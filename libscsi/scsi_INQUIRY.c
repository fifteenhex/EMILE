/*
 *
 * (c) 2004, 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <sys/types.h>

#include <scsi/scsi.h>

#include <macos/types.h>
#include <macos/errors.h>

#include "libscsi.h"

int scsi_INQUIRY(int target, volatile void *buffer, size_t count)
{
	const unsigned char cdb[6] = {
		INQUIRY,
		0,
		0,
		0,
		count,
		0
	};
	const TIB_t tib[2] = {
		{
			.opcode = op_no_inc,
			.param1 = (uint32_t) buffer,
			.param2 = count
		},
		{
			.opcode = op_stop,
			.param1 = 0,
			.param2 = 0
		}
	};

	return scsi_command(target, cdb, sizeof(cdb), tib);
}
