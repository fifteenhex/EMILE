/*
 *
 * (c) 2005-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */
#ifndef __LIBSTREAM_H__
#define __LIBSTREAM_H__

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <emile_alloc.h>

typedef enum {
	device_FLOPPY,
	device_SCSI,
} device_t;

typedef enum { fs_EXT2, fs_ISO9660, fs_CONTAINER, fs_BLOCK, fs_LAST } fs_t;

#define fs_NONE fs_LAST

struct stream_stat {
	int st_dev;
	off_t st_size;
	off_t st_base;
};

typedef struct device_io_t device_io_t;
typedef struct filesystem_io_t filesystem_io_t;
typedef void *stream_VOLUME;
typedef void *stream_DIR;

struct device_io_ops {
	int (*write_sector)(void *data, off_t offset, void *buffer,
			    size_t size);
	int (*read_sector)(void *data, off_t offset, void *buffer, size_t size);
	void (*close)(void *data);
	int (*get_blocksize)(void *data);
};

struct device_io_t {
	void *data;
	const struct device_io_ops *ops;
};

typedef int (*stream_init_t)(device_io_t *device, filesystem_io_t *fs);

struct filesystem_io_t {
	stream_VOLUME *(*mount)(device_io_t *device);
	void *(*open)(stream_VOLUME *volume, const char *path);
	int (*umount)(stream_VOLUME *volume);
	size_t (*read)(void *file, void *buf, size_t count);
	off_t (*lseek)(void *file, off_t offset, int whence);
	void (*close)(void *file);
	int (*fstat)(void *file, struct stream_stat *buf);

	/* Special version of read that periodically calls a callback */
	size_t (*read_with_progress)(void *file, void *buf, size_t count,
				     int (*cb)(off_t pos, void *data),
				     void *cb_data);
};

struct stream {
	/* device interface */

	device_io_t device;

	/* filesystem interface */

	const filesystem_io_t *fs;

	/* info */

	void *volume;
	void *file;
	fs_t fs_id;
	device_t device_id;
	int unit, partition;

	struct stream *sub_stream;
};

typedef struct stream stream_t;

extern stream_t *stream_open(char *dev);

extern int stream_read_sector(stream_t *stream, off_t offset, void *buffer,
			      size_t size);

static inline int stream_read(stream_t *stream, void *buf, size_t count)
{
	if (stream->fs->read)
		return stream->fs->read(stream->file, buf, count);
	else
		return -1;
}

static inline size_t
stream_read_with_progress_generic(stream_t *stream, void *buf, size_t count,
				  int (*cb)(off_t pos, void *data),
				  void *cb_data)
{
	size_t read = 0;
	//int blksize = (total_size + BAR_STEP - 1) / BAR_STEP;
	const int blksize = 32 * 1024;

	while (count) {
		int ret;
		size_t toread = blksize;

		if (toread > count)
			toread = count;

		ret = stream_read(stream, buf, toread);
		if (ret != toread)
			break;

		read += toread;
		buf += toread;
		count -= toread;

		cb(read, cb_data);
	}

	return read;
};

static inline int stream_read_with_progress(stream_t *stream, void *buf,
					    size_t count,
					    int (*cb)(off_t pos, void *data),
					    void *cb_data)
{
	if (stream->fs->read_with_progress)
		return stream->fs->read_with_progress(stream->file, buf, count,
						      cb, cb_data);
	else
		return stream_read_with_progress_generic(stream, buf, count, cb,
							 cb_data);
}

static inline off_t stream_lseek(stream_t *stream, off_t offset, int whence)
{
	if (stream->fs->lseek)
		return stream->fs->lseek(stream->file, offset, whence);
	else
		return -1;
}

static inline int stream_fstat(stream_t *stream, struct stream_stat *buf)
{
	int ret;

	if (stream->fs->fstat == NULL)
		return -1;

	ret = stream->fs->fstat(stream->file, buf);
	buf->st_dev = stream->unit;

	return ret;
}

extern void stream_set_default(int unit);

/* This wraps a stream in a decompressor if needed */
extern int stream_configure_decompressor(stream_t **stream);

static inline int stream_mount(stream_t *stream)
{
	stream->volume = stream->fs->mount(&stream->device);
	return 0;
}

static inline int stream_file_open(stream_t *stream, const char *path)
{
	stream->file = stream->fs->open(stream->volume, path);
	if (!stream->file)
		return -1;

	return 0;
}

static inline void stream_file_close(stream_t *stream)
{
	if (stream->fs && stream->fs->close)
		stream->fs->close(stream->file);
}

static inline void stream_umount(stream_t *stream)
{
	if (stream->fs && stream->fs->umount)
		stream->fs->umount(stream->volume);
}

static inline void stream_device_close(stream_t *stream)
{
	if (stream->device.ops && stream->device.ops->close)
		stream->device.ops->close(stream->device.data);
}

static inline int stream_shutdown(stream_t *stream)
{
	stream_file_close(stream);
	stream_umount(stream);
	stream_device_close(stream);

	free(stream);
	return 0;
}

static inline stream_t *stream_wrap_stream(stream_t *original_stream,
					   const filesystem_io_t *fs,
					   void *file)
{
	stream_t *wrapped_stream;

	wrapped_stream = zalloc(sizeof(*wrapped_stream));
	if (!wrapped_stream)
		return NULL;

	wrapped_stream->sub_stream = original_stream;
	wrapped_stream->fs = fs;
	wrapped_stream->file = file;

	return wrapped_stream;
}
#endif /* __LIBSTREAM_H__ */
