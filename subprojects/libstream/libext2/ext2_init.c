/*
 *
 * (c) 2008 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libext2.h"
#include "ext2.h"
#include "ext2_utils.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

#include "libext2.h"
#include "ext2.h"
#include "ext2_utils.h"

static void *ext2_open(stream_VOLUME *volume, const char *pathname)
{
	ext2_FILE *file;
	struct ext2_inode *inode;
	int ino;
	int ret;

	ino = ext2_seek_name((ext2_VOLUME *)volume, pathname);
	if (ino == 0)
		return NULL;

	inode = (struct ext2_inode *)malloc(sizeof(struct ext2_inode));
	if (inode == NULL)
		return NULL;

	ret = ext2_get_inode((ext2_VOLUME *)volume, ino, inode);
	if (ret == -1) {
		free(inode);
		return NULL;
	}
	if (S_ISLNK(inode->i_mode)) {
		static char buffer[1024];
		int i, last = 0;
		strcpy(buffer, pathname);
		for (i = 0; buffer[i]; i++)
			if (buffer[i] == '/')
				last = i;
		buffer[last] = '/';
		strcpy(buffer + last + 1, (char *)inode->i_block);
		ino = ext2_seek_name((ext2_VOLUME *)volume, buffer);
		if (ino == 0) {
			free(inode);
			return NULL;
		}
		ret = ext2_get_inode((ext2_VOLUME *)volume, ino, inode);
		if (ret == -1) {
			free(inode);
			return NULL;
		}
	}

	file = (ext2_FILE *)malloc(sizeof(ext2_FILE));
	if (file == NULL) {
		free(inode);
		return NULL;
	}
	file->volume = (ext2_VOLUME *)volume;
	file->inode = inode;
	file->offset = 0;

	return file;
}

static int is_ext2(device_io_t *device)
{
	struct ext2_super_block super;
	ext2_get_super(device, &super);
	if (super.s_magic == EXT2_SUPER_MAGIC)
		return 1;
	return 0;
}

static const struct filesystem_io_t ext2_io = {
	.mount = ext2_mount,
	.open = ext2_open,
	.read = ext2_read,
	.lseek = ext2_lseek,
	.close = ext2_close,
	.umount = ext2_umount,
	.fstat = ext2_fstat,
};

int ext2_init(device_io_t *device, const filesystem_io_t **fs)
{
	if (!is_ext2(device))
		return -1;

	*fs = &ext2_io;

	return 0;
}
