#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_LEN 500


int find_smallest_substring(char *str, char *pattern, int *index, int *window)
{
	char hash_str[255] = {0}, hash_pat[255] = {0};
	char str_len = strlen(str), pat_len = strlen(pattern);
	int i, count = 0, start = 0, succ = 0;

	*index = *window = 0;

	/*
	 * If str1 is not even equal to str2 then return.
	 */
	if (str_len < pat_len)
		return -EINVAL;

	for (i = 0; i < pat_len; i++)
		hash_pat[pattern[i]]++;

	for (i = 0; i < str_len; i++) {
		hash_str[str[i]]++;
		if((hash_str[str[i]] <= hash_pat[str[i]]) &&
		   (hash_pat[str[i]] > 0))
			count++;

		if (count == pat_len) {

			printf("before opz: succ: %d, start:%d, end: %d\n",
			       succ++, start, i);

			while ((hash_str[str[start]] > hash_pat[str[start]])
			       || (hash_pat[str[start]] == 0)){

				if ((hash_str[str[start]] >
				     hash_pat[str[start]]))
					hash_str[str[start]]--;

				start++;
			}

			printf("after opz: succ: %d, start:%d, end: %d\n",
			       succ, start, i);

			if ((!*index && !*window) ||
			    (*window > (i - start + 1))) {
				printf("Updating window prev (%d, %d) new (%d, %d)\n",
				       *index, *window, start, i - start + 1);
				*index = start;
				*window = i - start + 1;
			}
		}
	}

	return 0;
}

int count_substrings(char *str)
{
	char *sub_str;
	int len = strlen(str), i = 0, j = 0, k = 0;

	printf("Total estimated substrings %d\n", (len * ((len + 1) / 2)));

	// One extra char for NULL termination
	sub_str = malloc(len + 1);

	for (i = 0; i < len; i++) {
		for (j = i; j < len; j++) {
			//printf("i:%d j:%d len:%d\n", i, j,  j - i + 1);
			strncpy(sub_str, str + i, j - i + 1);
			sub_str[j - i + 1] = '\0';
			printf("substring %d: %s\n", ++k, sub_str);
		}
	}

	printf("Total actual substrings %d\n", k);

	return k;

}

int count_distint_chars(char *str)
{
	int i, count = strlen(str);
	char hash_str[255] = { 0 };

	for (i = 0;i < strlen(str); i++) {
		hash_str[str[i]]++;
		if (hash_str[str[i]] > 1)
			count--;
	}

	return count;
}

int count_kdistint_substrings(char *str, int k)
{
	char *sub_str, count = 0;
	int len = strlen(str), i = 0, j = 0, d = 0, c = 0;

	// One extra char for NULL termination
	sub_str = malloc(len + 1);

	for (i = 0; i < len; i++) {
		for (j = i; j < len; j++) {
			c++;
			strncpy(sub_str, str + i, j - i + 1);
			sub_str[j - i + 1] = '\0';
			d = count_distint_chars(sub_str);
			if (k == d)
				count++;
			printf("substring %d: %s distint:%d\n", c, sub_str, d);
		}
	}

	printf("No of k:%d distint substrings is %d\n", k, count);

	return count;

}

int main(int argc, char *argv[])
{
	char data[MAX_LEN] = {0}, data2[MAX_LEN] = {0};
	int choice, tmp1 , tmp2, i = 0;

	printf("Enter the data\n");
	scanf("%500[^\n]s", data);

	while (1) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Print the data\n");
		printf("2: Print the data with index\n");
		printf("3: Find smallest sub-string\n");
		printf("4: Count & Print substrings\n");
		printf("5: Count & Print k-distint substrings\n");
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
			printf("case 2\n");
			printf("Data output:\n");
			for (i = 0; i < strlen(data); i++)
				printf("%d:%c ", i, data[i]);
			printf("\n");
			break;
		case 3:
			printf("case 3\n");
			printf("Enter second string\n");
			scanf("%s", data2);
			find_smallest_substring(data, data2, &tmp1, &tmp2);
			printf("Substring start:%d end:%d\n", tmp1,
			       tmp1 + tmp2);
		case 4:
			printf("case 4\n");
			count_substrings(data);
			break;
		case 5:
			printf("case 5\n");
			printf("Enter number of distint chars:\n");
			scanf("%d", &tmp1);
			count_kdistint_substrings(data, tmp1);
			break;
		case 100:
			printf("case 100\n");
			break;
		default:
			printf("case default %d\n", choice);
			break;
		}
	}

	printf("End of main\n");

	return 0;
}
