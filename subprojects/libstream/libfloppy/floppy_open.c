/*
 *
 * (c) 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <stdlib.h>
#include <macos/devices.h>
#include <libstream.h>
#include <string.h>

#include "libfloppy.h"

static int floppy_get_blocksize(void *_device)
{
	return SECTOR_SIZE;
}

static void floppy_close(void *_device)
{
	floppy_device_t *device = (floppy_device_t *)_device;

	if (device == NULL)
		return;

	free(device);
}

/* offset is a block number
 * size is the number of bytes to read
 */

static int floppy_read_sector(void *_device, off_t offset, void *buffer,
			      size_t size)
{
	floppy_device_t *device = (floppy_device_t *)_device;
	OSErr err;
	ParamBlockRec_t param_block;

	/* check size to read is multiple of sector size */

	if (size & (SECTOR_SIZE - 1))
		return -1;

	memset(&param_block, 0, sizeof(param_block));

	param_block.ioBuffer = (unsigned long)buffer;
	param_block.ioVRefNum = device->unit + 1;
	param_block.ioRefNum = -5;
	param_block.ioReqCount = size;
	param_block.ioPosMode = fsFromStart;
	param_block.ioPosOffset = offset << SECTOR_SIZE_BITS;

	err = PBReadSync(&param_block);
	if (err != noErr)
		return -1;

	return 0;
}

const struct device_io_ops floppy_ops = {
	.read_sector = floppy_read_sector,
	.close = floppy_close,
	.get_blocksize = floppy_get_blocksize,
};

void *floppy_open(int unit)
{
	floppy_device_t *dev;

	dev = (floppy_device_t *)malloc(sizeof(floppy_device_t));

	if (dev == NULL)
		return NULL;

	dev->unit = unit;

	return dev;
}
