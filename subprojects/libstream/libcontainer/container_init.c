/*
 *
 * (c) 2008 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libcontainer.h"

#include <stdio.h>

#include <stdlib.h>

#include "libcontainer.h"
#include "container.h"

static void *container_open(stream_VOLUME *volume, const char *_path)
{
	container_FILE *file;
	device_io_t *device = (device_io_t *)volume;
	int block_size = device->ops->get_blocksize(device->data);
	unsigned long first, nbblocs;
	int ret;
	char *path = (char *)_path;

	first = strtol(path, &path, 0);
	if (*path != ',')
		return NULL;
	path++;
	nbblocs = strtol(path, &path, 0);
	if (*path != 0)
		return NULL;
	file = (container_FILE *)malloc(sizeof(container_FILE) + block_size);
	if (file == NULL)
		return NULL;

	file->container =
		(struct emile_container *)malloc(block_size * nbblocs);
	if (file->container == NULL) {
		free(file);
		return NULL;
	}

	ret = device->ops->read_sector(device->data, first, file->container,
				       block_size * nbblocs);
	if (ret == -1) {
		free(file->container);
		free(file);
	}

	file->offset = 0;
	file->device = device;
	file->current_block = 0;
	return file;
}

static const struct filesystem_io_t container_io = {
	.mount = container_mount,
	.umount = container_umount,
	.open = container_open,
	.read = container_read,
	.lseek = container_lseek,
	.close = container_close,
	.fstat = container_fstat,
};

int container_init(device_io_t *device, const filesystem_io_t **fs)
{
	*fs = &container_io;

	return 0;
}
