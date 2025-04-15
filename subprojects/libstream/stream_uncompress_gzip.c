/*
 * This is based on tinfgzip.c from tinf, we want the gzip header check bits
 * before decompressing.
 * 
 * tinfgzip - tiny gzip decompressor
 *
 * Copyright (c) 2003-2019 Joergen Ibsen
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must
 *      not claim that you wrote the original software. If you use this
 *      software in a product, an acknowledgment in the product
 *      documentation would be appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must
 *      not be misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *      distribution.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TINF_ADLER32 1
#define TINF_CRC32 0
#define TINF_ZLIB 0
#define TINF_GZIP 0
#define TINF_STREAM 1
#define TINF_RESTARTABLE 1
#define TINF_BUFFER 0
#define TINF_ASSERT(x)
#define TINFLATE_IMPLEMENTATION

#include <tinf_sf.h>

#include "libstream.h"
#include "stream_uncompress.h"

struct gzip_file {
	/* The fs stream that has the compressed data */
	stream_t *sub_stream;

	/* Our current file position in the uncompressed data */
	off_t pos;

	/* The position in the compressed data where we saw end of block */
	off_t last_cmp_eob;
	/* The positon in the uncompressed data where we saw end of block */
	off_t last_unc_eob;

	unsigned int data_start;
};

typedef enum {
	FTEXT = 1,
	FHCRC = 2,
	FEXTRA = 4,
	FNAME = 8,
	FCOMMENT = 16
} tinf_gzip_flag;

static bool gzip_parse_header(stream_t *stream, unsigned int *data_start)
{
	unsigned char header[10];
	unsigned char flg;
	unsigned int pos;
	int ret;

	/* Rewind the stream */
	stream_lseek(stream, 0, SEEK_SET);

	/* Read the header */
	ret = stream_read(stream, &header, sizeof(header));

	/* -- Check header -- */

	/* Check room for at least 10 byte header and 8 byte trailer */
	if (ret != sizeof(header)) {
		return false;
	}

	/* Check id bytes */
	if (header[0] != 0x1F || header[1] != 0x8B) {
		return false;
	}

	/* Check method is deflate */
	if (header[2] != 8) {
		return false;
	}

	/* Get flag byte */
	flg = header[3];

	/* Check that reserved bits are zero */
	if (flg & 0xE0) {
		return false;
	}

	/* Check that if any flags are set its only FNAME */
	if (flg & ~FNAME)
		return false;

	if (!data_start)
		goto out;

	/* -- Find start of compressed data -- */
	pos = sizeof(header);

	/* Skip file name if present */
	if (flg & FNAME) {
		unsigned char onebyte;
		do {
			stream_read(stream, &onebyte, sizeof(onebyte));
			pos++;
			if (!onebyte)
				break;
		} while (true);
	}

	*data_start = pos;

out:
	return true;
}

bool stream_is_gzip(stream_t *stream)
{
	return gzip_parse_header(stream, NULL);
}

struct gzip_cntx {
	struct gzip_file *gzip_file;

	/* How far have we decompressed so far? */
	off_t curr_pos;

	uint8_t *dst;

	/* How many bytes do we still need to read? */
	size_t need;

	/* Compressed file input buffer */
	uint8_t in_buf[4 * 1024];
	size_t in_count;
	off_t in_file_pos;

	/* Space for tinf data */
	struct tinf_data tinf_data;
};

static int gzip_cb_write_output(void *v, unsigned char c)
{
	struct gzip_cntx *cntx = v;
	struct gzip_file *gzip_file = cntx->gzip_file;

	/* Dude! stop it!! */
	if (!cntx->need)
		return -1;

	/* Are we still before the place we want to read? */
	if (cntx->curr_pos++ < gzip_file->pos)
		return 0;

	/* Store the byte and move the position forward */
	*cntx->dst++ = c;
	gzip_file->pos++;

	/* Are we done ? */
	cntx->need--;
	if (!cntx->need)
		return -1;

	/* Nope, keep the data coming! */
	return 0;
}

static int gzip_cb_read_input(void *v)
{
	struct gzip_cntx *cntx = v;
	struct gzip_file *gzip_file = cntx->gzip_file;
	stream_t *stream = gzip_file->sub_stream;
	off_t in_pos, buf_off;

	/* Read a fresh block of input */
	if (!cntx->in_count) {
		size_t in_size = sizeof(cntx->in_buf);

		int ret = stream_read(stream, cntx->in_buf, in_size);
		if (ret != in_size) {
			/* error */
			if (ret <= 0)
				return -1;

			/* short read, only acceptable at the end of the file */
			// todo (tm)
		}

		cntx->in_count = in_size;
	}

	in_pos = cntx->in_file_pos++;
	buf_off = in_pos % sizeof(cntx->in_buf);
	cntx->in_count--;

	return cntx->in_buf[buf_off];
}

static int gzip_cb_endofblock(void *v)
{
	struct gzip_cntx *cntx = v;
	struct gzip_file *gzip_file = cntx->gzip_file;

	//gzip_file->last_cmp_eob = cntx->in_file_pos + 1;
	//gzip_file->last_unc_eob = cntx->curr_pos + 1;

	return 0;
}

static size_t gzip_read(void *file, void *buf, size_t count)
{
	struct gzip_file *gzip_file = (struct gzip_file *)file;
	off_t file_offset = gzip_file->data_start;
	off_t last_unc_eob = gzip_file->last_unc_eob;
	struct gzip_cntx *cntx;
	int ret;

	cntx = zalloc(sizeof(*cntx));
	if (!cntx)
		return -1;

	/* 
	 * We might be restarting ... do we know where the end
	 * of a block was and is it before of the same as the
	 * position we'll start reading from?
	 */
	if (last_unc_eob && (gzip_file->pos >= last_unc_eob)) {
		off_t last_cmp_eob = gzip_file->last_cmp_eob;

		/* Yes, start decompressing from the end of the last block */
		cntx->curr_pos = last_unc_eob;
		cntx->in_file_pos = last_cmp_eob;
		file_offset += cntx->in_file_pos;
	}

	cntx->gzip_file = gzip_file;
	cntx->dst = buf;
	cntx->need = count;

	/* Make sure the sub stream is at the start of the compressed data */
	ret = stream_lseek(gzip_file->sub_stream, file_offset, SEEK_SET);
	if (ret != file_offset)
		return -1;

	ret = _tinf_stream_uncompress(&cntx->tinf_data, gzip_cb_read_input,
				      gzip_cb_write_output, gzip_cb_endofblock,
				      cntx);
	if (!((ret == TINF_OK) || (ret == TINF_CANCELLED)))
		goto out;

	/* decompressed everything apparently.. return the count */
	ret = count;

out:
	free(cntx);
	return ret;
}

static off_t gzip_lseek(void *file, off_t offset, int whence)
{
	struct gzip_file *gzip_file = file;

	switch (whence) {
	case SEEK_SET:
		gzip_file->pos = offset;
		return offset;
	}

	return -1;
}

static int gzip_fstat(void *file, struct stream_stat *buf)
{
	return -1;
}

static void gzip_close(void *file)
{
}

static const struct filesystem_io_t gzip_io = {
	.read = gzip_read,
	.lseek = gzip_lseek,
	.close = gzip_close,
	.fstat = gzip_fstat,
};

stream_t *stream_wrap_gzip(stream_t *stream)
{
	struct gzip_file *gzip_file;

	gzip_file = zalloc(sizeof(*gzip_file));
	if (!gzip_file)
		return NULL;

	/* Work out where the data starts */
	gzip_parse_header(stream, &gzip_file->data_start);

	gzip_file->sub_stream = stream;

	return stream_wrap_stream(stream, &gzip_io, gzip_file);
}
