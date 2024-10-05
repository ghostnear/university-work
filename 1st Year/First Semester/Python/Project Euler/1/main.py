def gaussSum(number):
    return number * (number + 1) // 2

def findSum(number):
    number -= 1
    return gaussSum(number // 3) * 3 + gaussSum(number // 5) * 5 - gaussSum(number // 15) * 15

print(findSum(1000))