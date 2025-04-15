/*
 *
 * (c) 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/fs.h>
#include <ext2fs/ext2_fs.h>
#include <libext2.h>

#include "ext2.h"

static void list(stream_VOLUME *volume, char *path)
{
	stream_DIR *dir;
	struct ext2_dir_entry_2 *entry;

	dir = ext2_opendir(volume, path);
	if (dir == NULL)
		return;
	while ((entry = ext2_readdir(dir)) != NULL) {
		if (entry->file_type == EXT2_FT_DIR)
			printf("%s/\n", entry->name);
		else
			printf("%s\n", entry->name);
	}
	ext2_closedir(dir);
}

int main(int argc, char **argv)
{
	stream_t stream;
	char *path;

	if (argc <= 1) {
		fprintf(stderr, "You must specify a device to open\n");
		exit(1);
	}

	path = argv[1];

	ext2_create_stream(&stream, path);
	list(stream.volume, path);
	stream_umount(&stream);
	stream_device_close(&stream);
	return (0);
}
