/*
 *
 * (c) 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#ifndef _LIBCONTAINER_H_
#define _LIBCONTAINER_H_

#include <sys/types.h>

#include <libstream.h>

struct emile_block {
	u_int32_t offset; /* offset of first block */
	u_int16_t count; /* number of blocks */
} __attribute__((packed));

struct emile_container {
	u_int32_t size;
	struct emile_block blocks[0];
} __attribute__((packed));

extern stream_VOLUME *container_mount(device_io_t *device);
extern int container_umount(stream_VOLUME *volume);
extern int container_init(device_io_t *device, const filesystem_io_t **fs);
extern void container_close(void *file);
extern off_t container_lseek(void *file, off_t offset, int whence);
extern size_t container_read(void *file, void *ptr, size_t size);
extern int container_fstat(void *file, struct stream_stat *buf);

#endif /* _LIBCONTAINER_H_ */
