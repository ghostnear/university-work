/*
 * 12.  2520 is the smallest number that can be divided by each of the numbers from 1 to 10 
 *      without any remainder. What is the smallest positive number that is divisible with no 
 *      reminder by all the numbers from 1 to 20?
 */

Int64 smallest_common_multiple(Int64 first, Int64 second)
{
    Int64 product = first * second;
    while (second != 0)
    {
        Int64 remainder = first % second;
        first = second;
        second = remainder;
    }
    return product / first;
}

Int64 smallest_nondivisible_number(Int64 start, Int64 end)
{
    Int64 result = start;
    for (Int64 number = start + 1; number <= end; number++)
        result = smallest_common_multiple(result, number);
    return result;
}

Console.WriteLine(smallest_nondivisible_number(1, 10));
Console.WriteLine(smallest_nondivisible_number(1, 20));
