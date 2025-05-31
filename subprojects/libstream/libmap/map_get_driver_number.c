/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libmap.h"

int map_get_driver_number(map_t *map)
{
	if (!map_is_valid(map))
		return -1;

	return read_short(struct_member_pointer(map, drivers.DrvrCount));
}
