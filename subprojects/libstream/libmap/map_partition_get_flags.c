/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libmap.h"

int map_partition_get_flags(map_t *map)
{
	return read_long(struct_member_pointer(map,partition.PartStatus));
}
