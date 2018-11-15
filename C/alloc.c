#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ALIGNMENT	8
#define ALIGN(size)	(((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define BUCKET_SIZE	10

typedef struct mheader {
	size_t size;
	unsigned int magic;
	struct mheader *next;
} mheader_t;

size_t hsize = ALIGN(sizeof(mheader));

mheader_t *free_blocks;

void *get_freeblock(size_t size)
{
	mheader_t *block = free_blocks;

	while (block) {
		if (size <= block->size)
			break;
		block = block->next;
	}

	return block
}

void *memalloc(size_t size)
{
	size_t bsize = ALIGN(size + hsize);
	mheader_t
}
