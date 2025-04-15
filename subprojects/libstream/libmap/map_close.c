/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <stdlib.h>
#include <unistd.h>

#include "libmap.h"

void map_close(void *_map)
{
	map_t *map = (map_t *)_map;

	map->device->ops->close(map->device);
	free(map->device);
	free(map);
}
