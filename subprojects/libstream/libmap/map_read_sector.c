/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "libmap.h"

int map_read_sector(void *_map, off_t offset, void *buffer, size_t size)
{
	map_t *map = (map_t *)_map;
	int ret;

	if (!map_partition_is_valid(map))
		return -1;

	offset += read_long(struct_member_pointer(map, partition.PyPartStart));

	ret = map->device->ops->read_sector(map->device->data, offset, buffer,
					    size);

	return ret;
}
