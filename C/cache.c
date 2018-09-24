#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define NANOSEC 1000000000

unsigned long gethrtime(void)
{
        struct timespec ts;

        if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) != 0) {
                return (-1);
        }

        return ((ts.tv_sec * NANOSEC) + ts.tv_nsec);
}

int exec_cpuid(int code, int *eax, int *ebx, int *ecx, int *edx)
{
	__asm__ volatile("cpuid;" //  call cpuid instruction
			:"=a"(*eax),"=b"(*ebx),"=c"(*ecx), "=d"(*edx)// output equal to "movl  %%eax %1"
			:"a"(code)// input equal to "movl %1, %%eax"
			//:"%eax","%ebx","%ecx","%edx"// clobbered register
	);

	return 0;
}

int cpuid_method(void)
{
	int eax = 0, ebx = 0, ecx = 0, edx = 0;

	exec_cpuid(0x80000006, &eax, &ebx, &ecx, &edx);

	printf("\nL2 Cache Size %d\n", ecx & 0xff);
}

int l1_cache_miss_method(void)
{
	volatile char *a, *b;
	register int pagesize, numofpages, i, numofiter, l1numoflines,
		 l1cachesize;
	unsigned long totalmem, start, end;
	long long int calc;

	pagesize = sysconf(_SC_PAGESIZE);
	numofpages = 10;
	l1cachesize = 32;
	l1numoflines = 1
	totalmem = pagesize * numofpages;

	printf("PAGESIZE = %d\n", pagesize);
	printf("TOTALMEM = %lu\n", totalmem);

	b = a = (char *) skrk(totalmem);

	/* Touch all pages */
	for (i = 0;i < numofpages;i++, a += (pagesize + 10))
		*a = 1;

	numofiter = totalmem / (l1numoflines * l1cachesize);

	for(incr=1; incr < MAX_GUESS; incr*=2) {
		start = gethrtime();
	        for(i=pagesize*NUM_PAGES/4; i<pagesize*(NUM_PAGES/4 + 1); i++)
		    a[i] += a[i+incr];
	        end = gethrtime();

		calc = (end - start) / (pagesize);

	        printf("Avg time (%d accesses, incr = %d) = %lld nsec\n", pagesize, incr, calc);
	        usleep(1000);
	}
}

int main(int argc, char *argv[])
{
	char choice;

	printf("Choose one of the following option\n");
	printf("0: CPUID\n");
	printf("1: L1 Cache miss method\n");
	printf("\n");
	scanf("%c", &choice);
	printf("Choice = %d\n", choice);
	switch (choice)
	{
	case '0':
		cpuid_method();
		break;
	case '1':
		l1_cache_miss_method();
		break;
	default:
		break;
	}

	return 0;
}
