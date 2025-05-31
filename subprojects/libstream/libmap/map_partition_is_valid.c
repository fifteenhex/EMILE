/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libmap.h"

int map_partition_is_valid(map_t *map)
{
	return read_short(struct_member_pointer(map,partition.Sig)) == MAP_SIGNATURE;
}
