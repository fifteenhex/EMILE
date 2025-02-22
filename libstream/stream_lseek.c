/*
 *
 * (c) 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include "libstream.h"

off_t stream_lseek(stream_t *stream, off_t offset, int whence)
{
	return stream->fs.lseek(stream->file, offset, whence);
}
