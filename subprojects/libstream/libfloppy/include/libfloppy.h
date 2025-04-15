/*
 *
 * (c) 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */
#ifndef __LIBFLOPY_H__
#define __LIBFLOPY_H__

#include <sys/types.h>
#include <unistd.h>

#define SECTOR_SIZE_BITS 9
#define SECTOR_SIZE (1 << (SECTOR_SIZE_BITS))
#define SECTOR_PER_TRACK 18
#define SIDE_NB 2

typedef struct {
	int unit;
} floppy_device_t;

extern void *floppy_open(int unit);
extern const struct device_io_ops floppy_ops;

#endif /* __LIBFLOPY_H__ */
