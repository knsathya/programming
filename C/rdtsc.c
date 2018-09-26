#include <stdio.h>
#include <stdint.h>


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

int main (int argc, char *argv)
{
	uint64_t base = find_base();

	printf("Base: %ld\n", base);

	return 0;
}
