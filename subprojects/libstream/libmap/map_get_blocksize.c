/*
 *
 * (c) 2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libmap.h"

int map_get_blocksize(void *_map)
{
	map_t *map = (map_t *)_map;

	return map->device->ops->get_blocksize(map->device->data);
}
