#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct mheader {
	size_t size;
} mheader_t;

void *mem_alloc(size_t size)
{
	size_t new_size = ALIGN_UP(size + sizeof(mheader));
}
