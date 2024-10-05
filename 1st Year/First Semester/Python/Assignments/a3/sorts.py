import os
import time
import timeit
from random import random

def clearScreen():
    if os.name == "nt":
        os.system('cls')
    else:
        os.system('clear')

def errorMessage(message):
    clearScreen()
    print(f"\n{ message }\nGoing back to where you were before...")
    time.sleep(2)

def generateRandomList(length, maxValue):
    list = []
    try:
        while length > 0:
            list.append(int(random() * maxValue))
            length -= 1
        return list
    except:
        return None

def generateDecreasingList(length):
    list = []
    try:
        while length > 0:
            list.append(length)
            length -= 1
        return list
    except:
        return None

def generateIncreasingList(length):
    return range(0, length)

def readNumber(message):
    try:
        val = int(input(message))
        return val
    except:
        errorMessage("A number is expected.")
        return 0

def startSorting(algorithm):
    clearScreen()

    list = []
    names = ["Selection", "Gnome", "Cocktail"]
    sortFunctions = [doSelectionSort, doGnomeSort, doCocktailSort]

    print(names[algorithm - 1] + " Sort has O(n^2) both worse and average complexity / O(n) in the best case so random / decreasing / increasing lists will be used.\n")
    randomListSizes = [1000, 2000, 4000, 8000, 16000]
    for currentSize in randomListSizes:
        list = generateRandomList(currentSize, 10 * currentSize)
        startTime = timeit.default_timer()
        sortFunctions[algorithm - 1](list)
        endTime = timeit.default_timer()
        print("Executed time for " + str(currentSize) + " random numbers: " + str(endTime - startTime) + " seconds.")
        list = generateDecreasingList(currentSize)
        startTime = timeit.default_timer()
        sortFunctions[algorithm - 1](list)
        endTime = timeit.default_timer()
        print("Executed time for " + str(currentSize) + " decreasing numbers: " + str(endTime - startTime) + " seconds.")
        list = generateIncreasingList(currentSize)
        startTime = timeit.default_timer()
        sortFunctions[algorithm - 1](list)
        endTime = timeit.default_timer()
        print("Executed time for " + str(currentSize) + " increasing numbers: " + str(endTime - startTime) + " seconds.\n")

    input("Press enter to continue.")

def printMainMenu():
    # Instruction for users
    print("\nUse your keyboard to navigate the following menus by writing the number of the option you want to use.\n")

    # Menu contents
    print("Main Menu:")
    print(" 1. Compare sorting times of Selection Sort.")
    print(" 2. Compare sorting times of Gnome Sort.")
    print(" 3. Compare sorting times of Cocktail Sort.")
    print(" 4. Exit.\n")

def main():
    # Main loop
    while True:
        clearScreen()
        printMainMenu()
        choice = readNumber("Action: ")
        if choice > 0 and choice < 4:
            startSorting(choice)
        elif choice == 4:
            break

    # Exit message
    clearScreen()
    print("\nBye!\n")

def doSelectionSort(list):
    length = len(list)
    for i in range(length):
        for j in range(i, length):
            if list[i] > list[j]:
                aux = list[i]
                list[i] = list[j]
                list[j] = aux

def doCocktailSort(list):
    start = 0
    end = len(list) - 1
    isSorted = False
    while not isSorted:
        # Go forwards
        isSorted = True
        for index in range(start, end):
            if list[index] > list[index + 1]:
                aux = list[index]
                list[index] = list[index + 1]
                list[index + 1] = aux
                isSorted = False

        # If sorted, stop
        if isSorted:
            break
        
        # Go backwards
        isSorted = True
        end -= 1

        for index in range(end - 1, start - 1, -1):
            if list[index] > list[index + 1]:
                aux = list[index]
                list[index] = list[index + 1]
                list[index + 1] = aux
                isSorted = False
        start += 1

def doGnomeSort(list):
    length = len(list)
    stepCount = 0
    index = 0
    while index < length:
        if index == 0:
            index += 1
        if list[index] >= list[index - 1]:
            index += 1
        else:
            aux = list[index]
            list[index] = list[index - 1]
            list[index - 1] = aux
            index -= 1
            stepCount += 1
main()