#include <stdio.h>
#include <stdlib.h>



void print_matrix_spiral(unsigned ms, unsigned ns, unsigned int me,
			 unsigned int ne, unsigned int n,
			 int data[][n])
{
	int i = ms, j = ns;

	printf("\nrs:%d re:%d cs:%d ce:%d\n", ms, me , ns, ne);

	if ((ms > me) || (ns > ne))
		return;

	/*
	 * Pseudo code:
	 *
	 * 1. if only one element, print it. otherwise,
	 * 2. print all the boundry items of array;
	 * 3. recurse with ms+1 me-1 and ns+1 ne-1;
	 *
	 */
	if (ms == me == ns == ne) {
		printf("data[%d][%d] - %d\n", i, j, data[i][j]);
		return;
	}

	//print row 0, col (1 - n-1)
	printf("Loop 1\n");
	for (i = ms, j = ns; j < ne; j++)
		printf("data[%d][%d] - %d\n", i, j, data[i][j]);

	printf("Loop 2\n");
	//print row (0 - m-1), col n-1
	for (i = ms, j = ne; i < me; i++)
		printf("data[%d][%d] - %d\n", i, j, data[i][j]);

	printf("Loop 3\n");
	//print row m-1, col (n-1 - 0)
	for (i = me, j = ne; j > ns; j--)
		printf("data[%d][%d] - %d\n", i, j, data[i][j]);

	printf("Loop 4\n");
	//print row (m-1 - 0), col 0
	for (i = me, j = ns; i > ms; i--)
		printf("data[%d][%d] - %d\n", i, j, data[i][j]);

	print_matrix_spiral(ms + 1, ns + 1, me-1, ne-1, n, data);

	return;
}

void test_spiral_matrix()
{
	int data_1[4][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 },
		{ 10, 11, 12 }
	};

	int data_2[2][4] = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 }
	};

	int data_3[3][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};

	print_matrix_spiral(0, 0, 3, 2, 3, data_1);
	print_matrix_spiral(0, 0, 1, 3, 4, data_2);
	print_matrix_spiral(0, 0, 2, 2, 3, data_3);

}

int main(int argc, char *argv[])
{
	test_spiral_matrix();
	return 0;
}
