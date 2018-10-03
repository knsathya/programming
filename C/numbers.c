#include <stdio.h>
#include <string.h>

int itoa(int num, int base, char *str)
{
	int i = 0, reminder;
	char isnegative = 0;

	if (!str)
		return -EINVAL;

	if (i == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return 0;
	}

	if (num < 0) {
		if (base == 10) {
			isnegative = 1;
			num = -1 * num;
		} else
			return -EINVAL;
	}


	while (num) {
		reminder = num % base;
		str[i++] = reminder < 10 ? reminder + '0' : reminder + 'a';
		num = num / 2;
	}

	if (isnegative)
		str[i++] = '-';

	str[i] = '\0';

	for (reminder = 0; reminder < i / 2; reminder++) {
		isnegative = str[reminder];
		str[reminder] = str[i - reminder - 1];
		str[i - reminder - 1] = isnegative;
	}


	return 0;
}
