#include <libiso9660.h>
#include <libstream.h>
#include "device.h"

static inline int iso9660_create_stream(stream_t *stream, const char *path)
{
	device_io_t *device = &stream->device;

	device_create_stream(stream, path);
	iso9660_init(device, &stream->fs);

	stream->volume = iso9660_mount(&stream->device);
	if (stream->volume == NULL)
		return -1;

	return 0;
}
