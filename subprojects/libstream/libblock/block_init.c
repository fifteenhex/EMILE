/*
 *
 * (c) 2008 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libblock.h"

#include <stdlib.h>

#include "libblock.h"
#include "block.h"

#define NB_SECTORS (18 * 2)

/*
 * path is "<first>,<size>"
 * where <first> is the offset of the first byte to read on the device
 * and <size> is the number of bytes to read then.
 */

static void *block_open(stream_VOLUME *volume, const char *_path)
{
	block_FILE *block;
	int blocksize =
		((device_io_t *)volume)
			->ops->get_blocksize(((device_io_t *)volume)->data);
	int first, size;
	char *path = (char *)_path;

	first = strtol(path, &path, 0);
	if ((*path != ',') && (*path != 0))
		return NULL;

	if (*path == ',') {
		path++;
		size = strtol(path, &path, 0);
		if (*path != 0)
			return NULL;
	} else
		size = -1;

	block = (block_FILE *)malloc(sizeof(block_FILE) +
				     NB_SECTORS * blocksize);
	if (block == NULL)
		return NULL;

	block->base = first;
	block->offset = 0;
	block->size = size;
	block->device = (device_io_t *)volume;
	block->current = -1;
	block->buffer_size = NB_SECTORS;

	return block;
}

static const filesystem_io_t block_io = {
	.mount = block_mount,
	.umount = block_umount,
	.open = block_open,
	.read = block_read,
	.lseek = block_lseek,
	.close = block_close,
	.fstat = block_fstat,
};

int block_init(device_io_t *device, const filesystem_io_t **fs)
{
	*fs = &block_io;

	return 0;
}
