/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <string.h>

#include "libmap.h"

int map_get_bootinfo(map_t *map, int *bootstart, int *bootsize, int *bootaddr,
		     int *bootentry, int *checksum, char *processor)
{
	if (!map_is_valid(map))
		return -1;

	*bootstart =
		read_long(struct_member_pointer(map, partition.LgBootStart));
	*bootsize = read_long(struct_member_pointer(map, partition.BootSize));
	*bootaddr = read_long(struct_member_pointer(map, partition.BootAddr));
	*bootentry = read_long(struct_member_pointer(map, partition.BootEntry));
	*checksum = read_long(struct_member_pointer(map, partition.BootCksum));
	strcpy(processor, map->partition.Processor);

	return 0;
}
