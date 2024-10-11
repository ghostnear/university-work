#include "gcd.h"
#include "big.h"

uint32_t binary_gcd(uint32_t first, uint32_t second)
{
	if(!first || !second)
		return (first | second);

    uint32_t exponent = 0;
    static uint32_t temp;

	while(!(first & 1) && !(second & 1))
    {
		first >>=1;
		second >>=1;
		exponent++;
	}

	do {
		while (!(first & 1))
			first >>=1;

		while (!(second & 1))
			second >>=1;

        temp = first;
        first = (first >= second) ? ((first - second) >> 1) : ((second - first) >> 1);
        second = (first >= second) ? second : temp;

	} while (!(first == second || first == 0));

	return (second << exponent);
}

uint32_t euclid_gcd(uint32_t first, uint32_t second)
{
	if(!first || !second)
		return (first | second);

    uint32_t remainder = 0;
    while(second > 0)
    {
        remainder = first % second;
        first = second;
        second = remainder;
    }
    return first;
}

BigNumber* big_gcd(BigNumber* first, BigNumber* second)
{
    while(!equal_number(first, second))
    {
        if(!compare_number(first, second))
        {
            BigNumber* aux = first;
            first = second;
            second = aux;
        }
        subtract_number(first, second);
    }

    return first;
}
