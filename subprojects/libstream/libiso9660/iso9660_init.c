/*
 *
 * (c) 2008 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <string.h>
#include <stdlib.h>

#include "libiso9660.h"
#include "iso9660.h"

static void *iso9660_open(stream_VOLUME *volume, const char *pathname)
{
	struct iso_directory_record *root;
	struct iso_directory_record *idr;
	iso9660_FILE *file;

	root = iso9660_get_root_node((iso9660_VOLUME *)volume);
	if (root == NULL)
		return NULL;

	idr = iso9660_get_node((iso9660_VOLUME *)volume, root, pathname);
	if (idr == NULL)
		return NULL;

	file = (iso9660_FILE *)malloc(sizeof(iso9660_FILE));
	if (file == NULL)
		return NULL;

	file->base = isonum_733((char *)idr->extent);
	file->size = isonum_733((char *)idr->size);
	file->offset = 0;
	file->current = -1;
	file->volume = (iso9660_VOLUME *)volume;

	free(idr);

	return file;
}

static int iso9660_fstat(void *_file, struct stream_stat *buf)
{
	iso9660_FILE *file = (iso9660_FILE *)_file;

	buf->st_size = file->size;
	buf->st_base = file->base;

	return 0;
}

static size_t iso9660_read(void *_file, void *buf, size_t count)
{
	iso9660_FILE *file = (iso9660_FILE *)_file;
	size_t read = 0;

	if (count > (file->size - file->offset))
		count = file->size - file->offset;

	while (count > 0) {
		size_t part;
		int offset_extent;
		int offset_index;

		offset_extent =
			file->base + (file->offset / ISO9660_EXTENT_SIZE);
		offset_index = file->offset % ISO9660_EXTENT_SIZE;

		if (file->current != offset_extent) {
			if ((offset_index == 0) &&
			    (count >= ISO9660_EXTENT_SIZE)) {
				/* direct i/o */

				int extents_nb;

				extents_nb = count / ISO9660_EXTENT_SIZE;

				part = extents_nb * ISO9660_EXTENT_SIZE;

				file->volume->device->ops->read_sector(
					file->volume->device->data,
					offset_extent, buf + read, part);
				file->offset += part;
				count -= part;
				read += part;

				continue;
			}

			file->current = offset_extent;
			file->volume->device->ops->read_sector(
				file->volume->device->data, offset_extent,
				file->buffer, ISO9660_EXTENT_SIZE);
		}

		part = ISO9660_EXTENT_SIZE - offset_index;
		if (count < part)
			part = count;

		memcpy(buf + read, file->buffer + offset_index, part);

		file->offset += part;
		count -= part;
		read += part;
	}

	return read;
}

static void iso9660_close(void *file)
{
	free(file);
}

static const filesystem_io_t iso9660_io = {
	.mount = iso9660_mount,
	.open = iso9660_open,
	.read = iso9660_read,
	.lseek = iso9660_lseek,
	.close = iso9660_close,
	.umount = iso9660_umount,
	.fstat = iso9660_fstat,
};

int iso9660_init(device_io_t *device, const filesystem_io_t **fs)
{
	*fs = &iso9660_io;

	return 0;
}
