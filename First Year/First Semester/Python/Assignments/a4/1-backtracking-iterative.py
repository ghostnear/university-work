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

def goToNextCombination(selectedCoins):
    transport = 1
    position = 0
    while position < len(selectedCoins):
        selectedCoins[position] += transport
        transport = selectedCoins[position] // 2
        selectedCoins[position] %= 2
        position += 1
    if transport > 0:
        return False
    return True

def canPay(selectedCoins, allCoins, amountToPay):
    sum = 0
    for index in range(len(allCoins)):
        sum += allCoins[index] * selectedCoins[index]
    if sum == amountToPay:
        return True
    return False

def generatePaymentMethods(allCoins, amountToPay):
    resultTable = []
    currentCoins = [0] * len(allCoins)      # We choose no coin in the beginning
    while goToNextCombination(currentCoins):
        if canPay(currentCoins, allCoins, amountToPay):
            currentResult = []
            for coin in range(len(allCoins)):
                if currentCoins[coin] == 1:
                    currentResult.append(allCoins[coin])
            resultTable.append(currentResult)
    if resultTable == []:
        print("There is no way that the requested ammount can be paid using the coins.")
    else:
        for paymentMethod in resultTable:
            print(paymentMethod)

def main():
    clearScreen()
    coinCount = 0
    try:
        coinCount = int(input("\nGive coin count: "))
    except:
        clearScreen()
        errorScreen("Value must be a number!")
        main()
        return
    allCoins = []
    try:
        allCoins = input("\nGive the values of the coins separated by spaces: ").split()
        if len(allCoins) != coinCount:
            errorScreen("Unexpected ammount of numbers!")
            main()
            return
        for index in range(0, len(allCoins)):
            allCoins[index] = int(allCoins[index])
    except:
        errorScreen("Value must be a number!")
        main()
        return
    amountToPay = 0
    try:
        amountToPay = int(input("\nGive amount to pay: "))
    except:
        clearScreen()
        errorScreen("Value must be a number!")
        main()
        return

    print("\nThese are the ways you can pay using these coins:\n")

    generatePaymentMethods(allCoins, amountToPay)

    input("\nPress enter to exit.\n\n")

main()