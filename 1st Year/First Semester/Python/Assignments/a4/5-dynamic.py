import os
import time

def clearScreen():
    if os.name == "nt":
        os.system('cls')
    else:
        os.system('clear')

def errorScreen(message):
    clearScreen()
    print(f"\n{ message }\nGoing back to where you were before...")
    time.sleep(2)

def splitRod(rodLength, slicePriceList):
    bestSlicing = [[]]
    bestPrice = [0]
    for currentSize in range(1, rodLength + 1):
        # Profit[n] = max of(Profit(i) + slicePriceList[n - i])
        bestSlicing.append([])
        bestPrice.append(0)

        # Go trough all of the previous results to get the best one
        for index in range(0, currentSize):
            (currentValue, currentResult) = (bestPrice[index], bestSlicing[index])

            # Add curent values and if bigger, save that
            currentValue += slicePriceList[currentSize - index - 1]
            if currentValue > bestPrice[currentSize]:
                bestPrice[currentSize] = currentValue
                bestSlicing[currentSize] = currentResult.copy()
                bestSlicing[currentSize].append(currentSize - index)
    print("Intermediate structures are as follows:\n")
    print(f"Array of best slicing profits per length: { bestPrice }")
    print(f"Array of best ways to partition those slices: { bestSlicing }")
    return (bestPrice[rodLength], bestSlicing[rodLength])

def main():
    clearScreen()
    rodLength = 0
    try:
        rodLength = int(input("\nGive rod length: "))
    except:
        clearScreen()
        errorScreen("Value must be a number!")
        main()
        return
    slicePriceList = input("\nGive the prices of the rod slices separated by spaces: ").split()
    if len(slicePriceList) != rodLength:
        errorScreen("Unexpected ammount of numbers!")
        main()
        return
    for index in range(0, len(slicePriceList)):
        slicePriceList[index] = int(slicePriceList[index])

    (bestValue, bestWay) = splitRod(rodLength, slicePriceList)

    print(f"\nThis is one way you can split the rod and get the maximum profit of { bestValue }:\n")

    for slice in bestWay:
        print(f"Length { slice }, value { slicePriceList[slice - 1] }.")

    input("\nPress enter to exit.\n\n")

main()