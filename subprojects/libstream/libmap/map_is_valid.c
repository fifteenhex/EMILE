/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libmap.h"

int map_is_valid(map_t *map)
{
	return read_short(struct_member_pointer(map, drivers.Sig)) == DD_SIGNATURE;
}
