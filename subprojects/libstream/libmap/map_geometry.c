/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libmap.h"

int map_geometry(map_t *map, int *block_size, int *block_count)
{
	if (!map_is_valid(map))
		return -1;

	*block_size = read_short(struct_member_pointer(map, drivers.BlkSize));
	*block_count = read_long(struct_member_pointer(map, drivers.BlkCount));

	return 0;
}
