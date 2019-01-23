#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PDATA_SIZE 10000
typedef unsigned long long data_t;
char pdata[PDATA_SIZE];

#define PRIdata "%llu"
#define PRIxdata "%llx"
#define SCNdata "%llu"

int count_setbits(data_t data)
{
	int count = 0;

	while (data > 0) {
		data = data & (data - 1);
		count++;
	}

	return count;
}

data_t gen_lmask(int l)
{
	return (((data_t)1 << l) - 1);
}

/*
 * Generates mask for a given bit range. MASK(l:m).
 *  0 < l < m
 *
 */
data_t gen_mask(int l, int m)
{
	data_t mask;

	return (((((data_t)1 << l) - 1) ^ (((data_t)1 << m) - 1)) + 1);
}

int bit_reverse(data_t data)
{
	int new_data;
}

char *print_bits(void *data, size_t size)
{
	int i, j, k = 0, c = 0;
	char *cdata = (char *) data;

	memset(pdata, 0, PDATA_SIZE);

	for (i = size - 1; i >= 0; i--)
		for (j = 7; j >= 0; j--) {
			if (cdata[i] >> j & 0x01)
				pdata[k++] = '1';
			else
				pdata[k++] = '0';
			if (c++ == 3) {
				if (!((i == 0) && (j < 3)))
					pdata[k++] = '-';
				c = 0;
			}
		}

	pdata[k] = '\0';

	return pdata;

}

void print_data(data_t data)
{
	printf("Data decimal: " PRIdata "hex: " PRIxdata "binary: %s\n", data,
	       data, print_bits(&data, sizeof(data_t)));
}

char *format_bdata(data_t data)
{
	return print_bits(&data, sizeof(data_t));
}

int main(int argc, char *argv[])
{
	data_t data = 0;
	int choice, l, h;

	printf("Enter the data\n");
	scanf(SCNdata, &data);

	while (1) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the data\n");
		printf("2: Count the number of set bits\n");
		printf("3: Generate mask for range of bits\n");
		printf("4: Generate mask for l bits\n");
		scanf("%d", &choice);

		switch(choice) {
		case 0:
			printf("case 0\n");
			return 0;
		case 1:
			printf("case 1\n");
			print_data(data);
			break;
		case 2:
			printf("case 2\n");
			printf("No of set bits %d\n", count_setbits(data));
			break;
		case 3:
			printf("case 3\n");
			printf("Enter lower bit index:\n");
			scanf("%d", &l);
			printf("Enter higher bit index:\n");
			scanf("%d", &h);
			printf("Mask for bit range %d..%d is \n", l, h);
			printf("Bit Map for 0x" PRIxdata " is:\n%s\n",
			       gen_mask(l, h),
			       format_bdata(gen_mask(l, h)));
			break;
		case 4:
			printf("case 4\n");
			printf("Enter lower bit index:\n");
			scanf("%d", &l);
			printf("Mask for bits %d is \n", l);
			printf("Bit Map for 0x" PRIxdata " is:\n%s\n",
			       gen_lmask(l),
			       format_bdata(gen_lmask(l)));
			break;
		default:
			printf("case default %d\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}
