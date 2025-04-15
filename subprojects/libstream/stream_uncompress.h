#include <stdbool.h>

#ifdef GZIP_SUPPORT
bool stream_is_gzip(stream_t *stream);
stream_t *stream_wrap_gzip(stream_t *stream);
#else
static inline bool stream_is_gzip(stream_t *stream)
{
	return false;
}

static inline stream_t *stream_wrap_gzip(stream_t *stream)
{
	return stream;
}
#endif
