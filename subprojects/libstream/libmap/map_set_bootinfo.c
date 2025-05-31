/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <string.h>

#include "libmap.h"

int map_set_bootinfo(map_t *map, int bootstart, int bootsize, int bootaddr,
		     int bootentry, int checksum, char *processor)
{
	if (!map_is_valid(map))
		return -1;

	write_long(struct_member_pointer(map, partition.LgBootStart), bootstart);
	write_long(struct_member_pointer(map, partition.BootSize), bootsize);
	write_long(struct_member_pointer(map, partition.BootAddr), bootaddr);
	write_long(struct_member_pointer(map, partition.BootEntry), bootentry);
	write_long(struct_member_pointer(map, partition.BootCksum), checksum);
	memset(map->partition.Processor, 0, sizeof(map->partition.Processor));
	strcpy(map->partition.Processor, processor);

	return 0;
}
