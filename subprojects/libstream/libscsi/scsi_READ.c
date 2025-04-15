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

/******************************************************************************
+=====-========-========-========-========-========-========-========-========+
|  Bit|   7    |   6    |   5    |   4    |   3    |   2    |   1    |   0    |
|Byte |        |        |        |        |        |        |        |        |
|=====+=======================================================================|
| 0   |                           Operation code (28h)                        |
|-----+-----------------------------------------------------------------------|
| 1   |   Logical unit number    |   DPO  |   FUA  |     Reserved    | RelAdr |
|-----+-----------------------------------------------------------------------|
| 2   | (MSB)                                                                 |
|-----+---                                                                 ---|
| 3   |                                                                       |
|-----+---                        Logical block address                    ---|
| 4   |                                                                       |
|-----+---                                                                 ---|
| 5   |                                                                 (LSB) |
|-----+-----------------------------------------------------------------------|
| 6   |                           Reserved                                    |
|-----+-----------------------------------------------------------------------|
| 7   | (MSB)                                                                 |
|-----+---                        Transfer length                             |
| 8   |                                                                 (LSB) |
|-----+-----------------------------------------------------------------------|
| 9   |                           Control                                     |
+=============================================================================+
******************************************************************************/

int scsi_READ(int target, unsigned long offset, unsigned short nb_blocks,
	      volatile void *buffer, int buffer_size)
{
	const unsigned char cdb[10] = { READ_10,
					0,
					(offset >> 24) & 0xFF,
					(offset >> 16) & 0xFF,
					(offset >> 8) & 0xFF,
					offset & 0xFF,
					0,
					(nb_blocks >> 8) & 0xFF,
					nb_blocks & 0xFF,
					0 };
	const TIB_t tib[2] = { { .opcode = op_no_inc,
				 .param1 = (uint32_t)buffer,
				 .param2 = buffer_size },
			       { .opcode = op_stop, .param1 = 0, .param2 = 0 } };

	return scsi_command(target, cdb, sizeof(cdb), tib);
}
