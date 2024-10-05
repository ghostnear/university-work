"""
    Task:
        The palindrome of a number is the number obtained by reversing the order of its digits (e.g. the palindrome of 237 is 732).
                                For a given natural number n, determine its palindrome.
"""

def getPalindrome(number):
    palindrome = 0
    while number > 0:
        palindrome = palindrome * 10 + number % 10
        number //= 10
    return palindrome
    

def main():
    data = int(input("Give number to get its palindrome.\nInput: "))
    print(f"The palindrome is { getPalindrome(data) }",)


main()