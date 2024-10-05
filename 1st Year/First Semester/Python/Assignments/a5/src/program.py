# 
#   Functions to deal with complex numbers -- list representation
#
def createComplexList(realPart, imaginaryPart):
    return [realPart, imaginaryPart]

def complexListToString(complexNumber):
    return f"complexNumber[0] = { complexNumber[0] }\ncomplexNumber[1] = { complexNumber[1] }i\n"

#
#   Functions to deal with complex numbers -- dict representation
#
def createComplexDictionary(realPart, imaginaryPart):
    return {
        'realPart': realPart,
        'imaginaryPart': imaginaryPart
    }

def complexDictionaryToString(complexNumber):
    return f"{ complexNumber }"

#
#   Functions that deal with both representations.
#
def getRealPart(number):
    # List representation
    if isinstance(number, list):
        return number[0]
    return number['realPart']

def getImaginaryPart(number):
    # List representation
    if isinstance(number, list):
        return number[1]
    return number['imaginaryPart']

#
#   Functions that deal with subarray/subsequence properties
#   They use the common 'both representations' functions.
#
def getMaximumSumSubarray(numberList : list):
    # Partial sums
    sumFromBeginning = [getRealPart(numberList[0])]
    for index in range(1, len(numberList)):
        sumFromBeginning.append(sumFromBeginning[index - 1] + getRealPart(numberList[index]))

    # Find the maximum sum subsequence
    maximumSum = sumFromBeginning[0]
    bestIndexes = [0, 0]
    for firstIndex in range(0, len(numberList)):
        for secondIndex in range(firstIndex, len(numberList)):
            currentSum = sumFromBeginning[secondIndex] - sumFromBeginning[firstIndex - 1]
            if currentSum > maximumSum:
                maximumSum = currentSum
                bestIndexes = [firstIndex, secondIndex]
    return (maximumSum, bestIndexes)

def printMaximumSumSubarray(numberList : list, currentRepresentation : str, stringFunction):
    (maximumSum, bestIndexes) = getMaximumSumSubarray(numberList)
    print(f"\nBest sum when using the { currentRepresentation } representation is: { maximumSum }.")
    print(f"The best subarray's length is { bestIndexes[1] - bestIndexes[0] + 1 } and has the following elements:\n")
    for index in range(bestIndexes[0], bestIndexes[1] + 1):
        print(stringFunction(numberList[index]))

def getDigitsFrequency(number):
    digitsFrequency = [0] * 10
    number = int(abs(number))
    while number > 0:
        digitsFrequency[number % 10] += 1
        number //= 10
    return digitsFrequency

def canBeWrittenUsingSameDigits(firstNumber, secondNumber):
    firstFrequency = getDigitsFrequency(firstNumber)
    secondFrequency = getDigitsFrequency(secondNumber)
    for index in range(0, 10):
        if firstFrequency[index] and secondFrequency[index] == 0:
            return False
    return True
    

def getLongestSameDigitSubarray(numberList : list):
    bestIndexes = None
    startIndex = -1
    currentIndex = 0
    while currentIndex < len(numberList):
        if canBeWrittenUsingSameDigits(getRealPart(numberList[currentIndex]), getImaginaryPart(numberList[currentIndex])):
            startIndex = currentIndex
            while currentIndex < len(numberList) and canBeWrittenUsingSameDigits(getRealPart(numberList[currentIndex]), getImaginaryPart(numberList[currentIndex])):
                currentIndex += 1
            
            if bestIndexes == None:
                bestIndexes = [startIndex, currentIndex]
            elif currentIndex - startIndex > bestIndexes[1] - bestIndexes[0]:
                bestIndexes = [startIndex, currentIndex]

        currentIndex += 1
    return bestIndexes

def printLongestSameDigitSubarray(numberList : list, currentRepresentation : str, stringFunction):
    bestSubarray = getLongestSameDigitSubarray(numberList)
    if bestSubarray == None:
        print(f"There is no longest subarray to be found using the { currentRepresentation } representation as none of the numbers have the required property.")
        return

    print(f"Longest subarray of numbers that can be written with the same digits is { bestSubarray[1] - bestSubarray[0] }.")
    print(f"Using the { currentRepresentation } representation, the elements are:")
    for index in range(bestSubarray[0], bestSubarray[1]):
        print(stringFunction(numberList[index]))

#
#   UI section
# 
import os
import time

def clearScreen():
    if os.name == "nt":
        os.system('cls')
    else:
        os.system('clear')

def waitForEnter():
    input("\nPress Enter to contine.")

def printError(message : str):
    clearScreen()
    print(f"\n{ message }\n")
    print("Going back to where you were before...")
    time.sleep(1.5)

def readInteger(message : str):
    try:
        result = int(input(message))
        return result
    except:
        printError("Your value is not a numerical one.")
        return None

def stringToAllForms(inputData : str):
    # Make sure the data is standard-conformant.
    inputData = inputData.replace('i','j').replace(' ', '')

    # Internal python representation
    internalNumber = complex(inputData)

    return (createComplexList(internalNumber.real, internalNumber.imag), createComplexDictionary(internalNumber.real, internalNumber.imag))

# Returns the currently read number in all forms.
def readComplexNumber(message : str):
    try:
        return stringToAllForms(input(message))
    except:
        print("Your value could not be parsed, try again.")
        return readComplexNumber(message)

# Read a complex number list and return it in both formats.
def readComplexNumberList():
    clearScreen()

    # Use both representations.
    numbersAsLists = []
    numbersAsDictionaries = []

    length = readInteger("\nInput the length of the complex number list: ")
    if length == None:
        return readComplexNumberList()

    for index in range(length):
        (currentComplexAsList, currentComplexAsDictionary) = readComplexNumber(f"Input number { index + 1 } (in z = a + bi form): ")
        numbersAsLists.append(currentComplexAsList)
        numbersAsDictionaries.append(currentComplexAsDictionary)

    return (numbersAsLists, numbersAsDictionaries)

# Prints the complex number list in a specified format.
def printComplexList(complexAsLists, complexAsDictionaries):
    clearScreen()

    # If list is empty, stop.
    if len(complexAsLists) == 0 or len(complexAsDictionaries) == 0:
        print("\nList is empty.")
        return

    print("\nIn what format should the list be printed?\n")
    print("1. List format.")
    print("2. Dictionary format.\n")
    chosenFormat = readInteger("Your choice: ")
    match chosenFormat:
        case 1:
            clearScreen()
            for element in complexAsLists:
                print(complexListToString(element))
        case 2:
            clearScreen()
            for element in complexAsDictionaries:
                print(complexDictionaryToString(element))
        case other:
            printError("Input was not a valid option.")
            printComplexList(complexAsLists, complexAsDictionaries)          


def printMainMenu():
    clearScreen()
    print("\n1. Read a list of complex numbers (in z = a + bi form).")
    print("2. Display the current list of numbers.")
    print("3. Display the length and elements of a longest subarray of numbers where both their real and imaginary parts can be written using the same base 10 digits.")
    print("4. Display the length and elements of a maximum subarray sum, when considering each number's real part.")
    print("5. Exit.\n")

if __name__ == "__main__":
    # App data
    complexAsLists = []
    complexAsDictionaries = []

    # The set of 10 initial numbers
    initialNumbers = [
        '1 + 3i',
        '31i',
        '33 +    i',
        '111',
        '11-313i',
        '  -  3131    +  5  i',
        '-10 - 10i',
        '0 - 0i',
        '0',
        '110 - 101010i'
    ]
    for number in initialNumbers:
        try:
            (currentNumberAsList, currentNumberAsDictionary) = stringToAllForms(number)
            complexAsLists.append(currentNumberAsList)
            complexAsDictionaries.append(currentNumberAsDictionary)
        except: # This should not happen EVER as I put the numbers there but just in case.
            print(f"Error while parsing number: { number }!")
            waitForEnter()

    # Main loop
    while True:
        printMainMenu()
        choice = readInteger("Selected action: ")
        match choice:
            case 1:
                (complexAsLists, complexAsDictionaries) = readComplexNumberList()
            case 2:
                printComplexList(complexAsLists, complexAsDictionaries)

                waitForEnter()
            case 3:
                clearScreen()
                print()
                printLongestSameDigitSubarray(complexAsLists, 'list', complexListToString)
                printLongestSameDigitSubarray(complexAsDictionaries, 'dictionary', complexDictionaryToString)
                waitForEnter()
            case 4:
                clearScreen()
                printMaximumSumSubarray(complexAsLists, 'list', complexListToString)
                printMaximumSumSubarray(complexAsDictionaries, 'dictionary', complexDictionaryToString)
                waitForEnter()

            case 5:
                break

            case None:
                pass    # Already taken care of in the input function.

            case other:
                printError("Input was not a valid option.")
    
    # End message
    clearScreen()
    print("\nGoodbye!\n")