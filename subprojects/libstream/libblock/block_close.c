/*
 *
 * (c) 2005 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#include <stdlib.h>

#include "libblock.h"

void block_close(void *file)
{
	if (file == NULL)
		return;

	free(file);
}
