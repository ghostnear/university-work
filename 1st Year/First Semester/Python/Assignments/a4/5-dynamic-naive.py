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
    # Only one way to do it if length 1
    if rodLength == 1:
        return (slicePriceList[0], [1])
    
    # Profit[n] = max of(Profit(i) + slicePriceList[n - i])
    maximum = -1
    bestSlicing = []
    for index in range(0, rodLength):
        # Get previous best result
        (currentValue, currentList) = splitRod(index, slicePriceList)

        # Add curent values and if bigger, save that
        currentValue += slicePriceList[rodLength - index - 1]
        if currentValue > maximum:
            maximum = currentValue
            bestSlicing = currentList
            bestSlicing.append(rodLength - index)
    return (maximum, bestSlicing)

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