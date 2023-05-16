"""
    Task:
        Generate the largest perfect number smaller than a given natural number n.
                If such a number does not exist, a message should be displayed.
        A number is perfect if it is equal to the sum of its divisors, except itself.
                (e.g. 6 is a perfect number, as 6=1+2+3).
"""

def sumDivisors(number):
    sum = 0
    divisor = 1
    while divisor * divisor <= number:
        if number % divisor == 0:
            sum += divisor
            if divisor != number // divisor:
                sum += number // divisor
        divisor += 1
    return sum


def isPerfect(number):
    if sumDivisors(number) == 2 * number:
        return True
    return False

def main():
    data = int(input("Introduce a number to get the largest perfect number smaller than it.\nInput: "))
    data -= 1
    while data > 4:
        if isPerfect(data):
            print(f"The number is { data }.")
            return # remove this to get all of the perfect numbers
            # they should be in this order: 6, 28, 496, 8128...
        data -= 1
    print("There is no perfect number smaller than the input.")

main()