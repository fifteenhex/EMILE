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

#include "iso9660.h"

int main(int argc, char **argv)
{
	stream_t stream;
	char *path;
	char buffer[512];
	size_t size;
	int get_info = 0;
	int arg = 1;
	char *devname;
	int ret;

	if ((argc > arg) && (strcmp(argv[arg], "-i") == 0)) {
		arg++;
		get_info = 1;
	}

	if (argc > arg)
		devname = argv[arg++];
	else
		devname = "/dev/cdrom";

	if (argc > arg)
		path = argv[arg++];
	else
		path = "/";

	iso9660_create_stream(&stream, devname);
	ret = stream_file_open(&stream, path);

	if (ret) {
		fprintf(stderr, "%s not found\n", path);
		return -1;
	}

	if (get_info) {
		struct stream_stat st;

		stream_fstat(&stream, &st);
		printf("%jd %jd\n", st.st_base * 4, st.st_size);
	} else {
		while ((size = stream_read(&stream, buffer, sizeof(buffer)) >
			       0))
			write(STDOUT_FILENO, buffer, size);
	}

	stream_file_close(&stream);
	stream_umount(&stream);
	stream_device_close(&stream);

	return 0;
}
