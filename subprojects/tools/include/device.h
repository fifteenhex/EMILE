/*
 *
 * (c) 2005-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <libstream.h>

extern int device_sector_size;
extern long device_open(const char *device, int flags);
extern const struct device_io_ops device_device_io_ops;

static inline void device_create_stream(stream_t *stream, const char *path)
{
	device_io_t *device = &stream->device;

	device_sector_size = 2048;
	device->data = (void *)device_open(path, O_RDONLY);
	device->ops = &device_device_io_ops;
}
