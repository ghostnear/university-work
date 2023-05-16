"""
    Task:
        Generate the largest prime number smaller than a given natural number n.
            If such a number does not exist, a message should be displayed.
"""

def isPrime(number):
    # 2 is guaranteed prime
    if number == 2:
        return True

    # even numbers and numbers smaller than 2 are not prime
    if number < 2 or number % 2 == 0:
        return False
    
    # if one proper divisor is found, number is not prime
    divisor = 3
    while divisor * divisor <= number and number % divisor != 0:
        divisor += 2
    if number % divisor == 0:
        return False

    # is prime
    return True

def largestSmallerPrime(number):
    # 3 has special case
    if number == 3:
        return 2

    # make even numbers odd so that we can use 2-sized steps
    number -= 1 - (number % 2)

    # go down and check for primes
    for i in range(number, 3, -2):
        if isPrime(i):
            return i


def main():
    data = int(input("Introduce a number to get the largest prime number smaller than it.\nInput: "))
    if data < 3:
        print("There is no such number for your specified input.")
    else:
        print(f"The number is { largestSmallerPrime(data) }")

main()