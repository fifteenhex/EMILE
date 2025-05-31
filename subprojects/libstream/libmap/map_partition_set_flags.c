/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libmap.h"

int map_partition_set_flags(map_t *map, int flags)
{
	write_long(struct_member_pointer(map, partition.PartStatus), flags);

	return 0;
}
