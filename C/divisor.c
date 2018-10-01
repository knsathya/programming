#include <stdio.h>

int divide(int divident, int divisor)
{
	int sign, count = 0;

	if (divident < divisor)
		return 0;

	sign = (divident < 0) ^ (divisor < 0) ? -1 : 1;

	while (divident >= divisor) {
		divident = divident - divisor;
		count++;
	}

	return sign * count;
}

int reminder(int divident, int divisor)
{
	int count = divide(divident, divisor);

	if (!count)
		return divisor - divident;
	else
		return divident - (count * divisor);
}

int main(int argc, char *argv[]) {
	int input1, choice, input2;

	while(1) {
		printf("Choose one of the following option:\n");
		printf("0: Exit the program\n");
		printf("1: Divison using subraction\n");
		printf("2: Reminder using subraction\n");
		scanf("%d", &choice);

		switch(choice) {
		case 0:
			printf("case 0\n");
			return 0;
		case 1:
			printf("Enter the divident\n");
			scanf("%d", &input1);
			printf("Enter the divisor\n");
			scanf("%d", &input2);

			printf("Local:%d Base:%d\n",
			       divide(input1, input2),
			       input1 / input2);
			break;
		case 2:
			printf("Enter the divident\n");
			scanf("%d", &input1);
			printf("Enter the divisor\n");
			scanf("%d", &input2);

			printf("Local:%d Base:%d\n",
			       reminder(input1, input2),
			       input1 % input2);
			break;
		default:
			break;
		}
	}
	return 0;
}
