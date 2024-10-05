import os
import time
from random import random

# Already did the first 3 before, rip
# Teacher said it's fine, these 2 can be ignored.
# 4 - permutation sort
# 6 - shell

def clearScreen():
    if os.name == "nt":
        os.system('cls')
    else:
        os.system('clear')

def errorScreen(message):
    clearScreen()
    print(f"\n{ message }\nGoing back to where you were before...")
    time.sleep(2)

def generateRandomList():
    clearScreen()
    list = []
    try:
        n = int(input("\nType the length of the generated list here (should be <= 30): "))
        if n > 30:
            errorScreen("N is too big, please try again.")
            return generateRandomList()
        if n < 2:
            errorScreen("The list can't be sorted if it is this small, plese try again.")
            return generateRandomList()
        while n > 0:
            list.append(int(random() * 100))
            n -= 1
        return list
    except:
        return None

def doInput(message):
    try:
        val = int(input(message))
        return val
    except:
        errorScreen("A number is expected.")
        return 0

def startSort(algo, list):
    # If we do not have a list, error then go to menu.
    if list == None:
        errorScreen("You have not generated a list yet.")
        return

    clearScreen()

    # Get valid input
    step = 0
    while step == 0:
        step = doInput("\nChoose the step interval in which to display the partially sorted list: ")
    
    # Algos
    if algo == 1:
        doSelection(list, step)
    elif algo == 2:
        doGnome(list, step)
    elif algo == 3:
        doCocktail(list, step)
    time.sleep(5)

def printMainMenu(list):
    # Instruction for users
    print("\nUse your keyboard to navigate the following menus by writing the number of the option you want to use.\n")

    # Print list only if it exists
    if list != None:
        print(f"Current list is: { list }\n")

    # Menu contents
    print("Mein Menu:")
    print(" 1. Generate a list of N natural numbers.")
    print(" 2. Sort the already generated list using Selection Sort.")
    print(" 3. Sort the already generated list using Gnome Sort.")
    print(" 4. Sort the already generated list using Cocktail Sort.")
    print(" 5. Exit.\n")

def partialPrint(list, stepCount):
    print(f"{stepCount:3d}: { list }")
    time.sleep(0.5)

def main():
    # The list of values, empty at the beginning
    list = None

    # Main loop
    while True:
        clearScreen()
        printMainMenu(list)
        choice = doInput("Action: ")
        if choice == 1:
            list = generateRandomList()
        elif choice > 1 and choice < 5:
            startSort(choice - 1, list)
            list = None
        elif choice == 5:
            break

    # Exit message
    clearScreen()
    print("\nBye!\n")

# Selection Sort
def doSelection(list, stepLimit):
    length = len(list)
    stepCount = 0
    clearScreen()
    for i in range(length):
        for j in range(i, length):
            if list[i] > list[j]:
                aux = list[i]
                list[i] = list[j]
                list[j] = aux
                stepCount += 1
                if stepCount % stepLimit == 0:
                    partialPrint(list, stepCount)
    print("\nFinal:")
    partialPrint(list, stepCount)

# Cocktail Sort
def doCocktail(list, stepLimit):
    stepCount = 0
    start = 0
    end = len(list) - 1
    isSorted = False
    clearScreen()
    while not isSorted:
        # Go forwards
        isSorted = True
        for i in range(start, end):
            if list[i] > list[i + 1]:
                aux = list[i]
                list[i] = list[i + 1]
                list[i + 1] = aux
                isSorted = False
                stepCount += 1
                if stepCount % stepLimit == 0:
                    partialPrint(list, stepCount)

        # If sorted, stop
        if isSorted:
            break
        
        # Go backwards
        isSorted = True
        end -= 1

        for i in range(end - 1, start - 1, -1):
            if list[i] > list[i + 1]:
                aux = list[i]
                list[i] = list[i + 1]
                list[i + 1] = aux
                isSorted = False
                stepCount += 1
                if stepCount % stepLimit == 0:
                    partialPrint(list, stepCount)

        start += 1

    print("\nFinal:")
    partialPrint(list, stepCount)

# Gnome Sort
def doGnome(list, stepLimit):
    length = len(list)
    stepCount = 0
    clearScreen()
    i = 0
    while i < length:
        if i == 0:
            i += 1
        if list[i] >= list[i - 1]:
            i += 1
        else:
            aux = list[i]
            list[i] = list[i - 1]
            list[i - 1] = aux
            i -= 1
            stepCount += 1
            if stepCount % stepLimit == 0:
                partialPrint(list, stepCount)

    print("\nFinal:")
    partialPrint(list, stepCount)

main()