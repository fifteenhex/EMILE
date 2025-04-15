#include <libext2.h>
#include <libstream.h>
#include "device.h"

static inline int ext2_create_stream(stream_t *stream, const char *path)
{
	device_io_t *device = &stream->device;

	device_create_stream(stream, path);
	device_sector_size = 512;

	stream->volume = ext2_mount(device);
	if (stream->volume == NULL)
		return -1;

	return 0;
}
