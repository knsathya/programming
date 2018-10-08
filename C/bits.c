#include <stdio.h>
#include <stdlib.h>

typedef int data_t;
#define PRIdata "%d"
#define SCNdata "%d"

int count_setbits(data_t data)
{
	int count = 0;

	while (data > 0) {
		data = data & (data - 1);
		count++;
	}

	return count;
}

int bit_reverse(data_t data)
{
	int new_data;
}

char *print_bits(void *data, size_t size)
{
	int i, j, k = 0, c = 0;
	char *cdata = (char *) data;
	char *pdata = (char *) malloc(size * 15);

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
	char *bdata = print_bits(&data, sizeof(data_t));

	printf("Data decimal: %d hex: %x binary: %s\n", data, data, bdata);
	free(bdata);
}

int main(int argc, char *argv[])
{
	data_t data = 0;
	int choice;

	printf("Enter the data\n");
	scanf(SCNdata, &data);

	while (1) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the data\n");
		printf("2: Count the number of set bits\n");
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
			printf("case 3\n");
			printf("No of set bits " PRIdata "\n",
			       count_setbits(data));
			break;
		default:
			printf("case default " PRIdata "\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}
