#include "libstream.h"
#include "stream_uncompress.h"

int stream_configure_decompressor(stream_t **stream)
{
	stream_t *original_stream = *stream;

	if (stream_is_gzip(original_stream))
		*stream = stream_wrap_gzip(original_stream);
	else {
		// nop
	}

	/* Make sure the stream is back at zero */
	stream_lseek(*stream, 0, SEEK_SET);

	return 0;
}
