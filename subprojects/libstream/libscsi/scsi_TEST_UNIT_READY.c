/*
 *
 * (c) 2006 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <sys/types.h>
#include <stdio.h>

#include <scsi/scsi.h>

#include <macos/types.h>
#include <macos/errors.h>

#include "libscsi.h"

static const unsigned char cdb[6] = { TEST_UNIT_READY, 0, 0, 0, 0, 0 };

int scsi_TEST_UNIT_READY(int target)
{
	return scsi_command(target, cdb, sizeof(cdb), NULL);
}
