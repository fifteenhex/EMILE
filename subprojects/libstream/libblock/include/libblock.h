/*
 *
 * (c) 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <sys/types.h>
#include <unistd.h>

#include <libstream.h>

extern int block_init(device_io_t *device, const filesystem_io_t **fs);
extern stream_VOLUME *block_mount(device_io_t *device);
extern int block_umount(stream_VOLUME *volume);
extern void block_close(void *file);
extern size_t block_read(void *file, void *ptr, size_t size);
extern off_t block_lseek(void *file, off_t offset, int whence);
extern int block_fstat(void *file, struct stream_stat *buf);
