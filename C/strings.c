#include <stdio.h>
#include <string.h>

#define MAX_LEN 500


char *find_smallest_substring(char *str1, char *str2, int *min, int *max)
{
	char hash1[255] = 0, hash2[255] = 0;
	char len1 = strlen(str1); len2 = (str2);
	int i, j;

	*min = *max = 0;

	/*
	 * If str1 is not even equal to str2 then return.
	 */
	if (len1 < len2)
		return NULL;

	for (i = 0; i < len2; i++)
		hash2[str2[i]]++;

	for (i = 0; i < len1; i++)
		hash1[str1[i]]++;

	for (i = 0; i < len2; i++)
		if(hash1[str2[i]] < hash2[str2[i]])
			return NULL;

}

int main(int argc, char *argv[])
{
	char data[MAX_LEN] = 0;
	int choice;

	printf("Enter the data\n");
	scanf("%s", &data);

	while (1) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the data\n");
		printf("2: Find whether pangram or not\n");
		scanf("%d", &choice);

		switch(choice) {
		case 0:
			printf("case 0\n");
			return 0;
		case 1:
			printf("case 1\n");
			printf("Data output:\n");
			printf("%s\n", data);
			break;
		case 2:
			printf("case 3\n");
			break;
		case 100:
			printf("case 100\n");
			break;
		default:
			printf("case default " PRIdata "\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}
