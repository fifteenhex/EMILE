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

#include "ext2.h"

int main(int argc, char **argv)
{
	stream_t stream;
	char *path;
	char buffer[512];
	ssize_t size;
	int arg = 1;
	char *devname;

	if (argc <= arg)
		return 1;
	devname = argv[arg++];

	if (argc > arg)
		path = argv[arg++];
	else
		path = "/";

	ext2_create_stream(&stream, devname);
	stream_file_open(&stream, path);

	//file = ext2_open(volume, path);
	//if (file == NULL)
	//{
	//	fprintf(stderr, "%s not found\n", path);
	//	return -1;
	//}

	while ((size = stream_read(&stream, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, size);

	stream_file_close(&stream);
	stream_umount(&stream);
	stream_device_close(&stream);

	return 0;
}
