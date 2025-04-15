/*
 *
 * (c) 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#ifndef __LIBISO9660_H__
#define __LIBISO9660_H__

#include <unistd.h>
#include <linux/iso_fs.h>

#include <libstream.h>

extern int iso9660_init(device_io_t *device, const filesystem_io_t **fs);
extern stream_VOLUME *iso9660_mount(device_io_t *device);
extern int iso9660_umount(stream_VOLUME *volume);
extern stream_DIR *iso9660_opendir(stream_VOLUME *, char *name);
extern int iso9660_closedir(stream_DIR *dir);
extern struct iso_directory_record *iso9660_readdir(stream_DIR *dir);
extern int iso9660_is_directory(struct iso_directory_record *idr);
extern off_t iso9660_lseek(void *file, off_t offset, int whence);
extern void iso9660_name(stream_VOLUME *volume,
			 struct iso_directory_record *idr, char *buffer);

#endif /* __LIBISO9660_H__ */
