/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <stdlib.h>
#include <unistd.h>

#include "libmap.h"

int map_get_number(map_t *map)
{
	return read_long(struct_member_pointer(map, partition.MapBlkCnt));
}
