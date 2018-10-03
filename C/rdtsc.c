#include <stdio.h>
#include <stdint.h>

#define KB 1024
#define MB 1024 * KB

size_t cache_size = {
	1 * KB,
	2 * KB,
	4 * KB,
	8 * KB,
	16 * KB,
	32 * KB,
	64 * KB,
	128 * KB,
	256 * KB,
	512 * KB,
	1 * MB,
	2 * MB,
	4 * MB,
	8 * MB,
	16 * MB,
	32 * MB,
	64 * MB,
	128 * MB
};

uint64_t rdtsc()
{
	uint64_t a, d;
	__asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
	return (d<<32) | a;
}

uint64_t find_base()
{
        uint64_t cycles_low, cycles_high;
	uint64_t total = 0;
	int i;

	for (i = 0; i < 1000; i++) {
		cycles_low = rdtsc();
		cycles_high = rdtsc();
	        total = total + (cycles_high - cycles_low);
	}

	return total / 1000;
}

void test_cache(uint64_t base)
{
	int len = sizeof(cache_size) / sizeof(size_t);
	int i = 0;
	int max_cache = 128 * MB;
	char *data = (char *) malloc(max_cache);

	for (i = 0; i < max_cache; i++)
		data[i] = 1;

	for(i = 0; i < len; i++) {
	}

}

int main (int argc, char *argv)
{
	uint64_t base = find_base();

	printf("Base: %ld\n", base);

	return 0;
}
