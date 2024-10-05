#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	printf("%ld\n", sizeof(int));
	printf("%d\n", INT_MIN);
	printf("%d\n", INT_MAX);
	printf("%ld\n", sizeof(double));
	printf("%e\n", DBL_MIN);
	printf("%e\n", DBL_MAX);
	return 0;
}
