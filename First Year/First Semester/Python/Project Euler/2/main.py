def sumOfEvenFibonacciNumbers(limit):
    first = 1
    second = 1
    result = 0
    while second < limit:
        if second % 2 == 0:
            result += second
        sum = first + second
        first = second
        second = sum
    return result

print(sumOfEvenFibonacciNumbers(4000000))