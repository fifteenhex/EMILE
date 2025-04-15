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

static const unsigned char read_capacity_cdb[10] = {
	READ_CAPACITY, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int scsi_READ_CAPACITY(int target, volatile void *buffer, size_t count)
{
	const TIB_t tib[2] = { { .opcode = op_no_inc,
				 .param1 = (uint32_t)buffer,
				 .param2 = count },
			       { .opcode = op_stop, .param1 = 0, .param2 = 0 } };

	return scsi_command(target, read_capacity_cdb,
			    sizeof(read_capacity_cdb), tib);
}
