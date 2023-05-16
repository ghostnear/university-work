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

def generateResultTable(allCoins, amountToPay, currentCoins, resultTable):
    selectedCoin = 0
    if currentCoins != []:
        selectedCoin = currentCoins[-1] + 1
    while selectedCoin < len(allCoins):
        amountToPay -= allCoins[selectedCoin]
        currentCoins.append(selectedCoin)
        if(amountToPay > 0):
            generateResultTable(allCoins, amountToPay, currentCoins, resultTable)
        elif(amountToPay == 0):
            currentResult = []
            for coin in currentCoins:
                currentResult.append(allCoins[coin])
            resultTable.append(currentResult)
        currentCoins.pop()
        amountToPay += allCoins[selectedCoin]
        selectedCoin += 1

def generatePaymentMethods(allCoins, amountToPay):
    # Reverse the list for faster generation
    allCoins.sort(reverse = True)
    resultTable = []
    generateResultTable(allCoins, amountToPay, [], resultTable)
    if len(resultTable) < 1:
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