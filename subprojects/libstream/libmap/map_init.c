/*
 *
 * (c) 2008 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libmap.h"

static const struct device_io_ops map_ops = {
	.read_sector = map_read_sector,
	.close = map_close,
	.get_blocksize = map_get_blocksize,
};

int map_init(device_io_t *device, int partition)
{
	int ret;
	map_t *map;

	map = map_open(device);
	if (map == NULL)
		return -1;

	ret = map_read(map, partition);
	if (ret == -1) {
		map_close(map);
		return -1;
	}

	device->data = map;
	device->ops = &map_ops;

	return 0;
}
