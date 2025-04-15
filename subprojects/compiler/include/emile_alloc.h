#include <stdlib.h>
#include <string.h>

static inline void *zalloc(size_t size)
{
	void *p = malloc(size);

	if (p)
		memset(p, 0, size);

	return p;
}
