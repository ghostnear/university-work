#
#   UI.
#

import os
import functions as service

def clearScreen() -> None:
    if os.name == "nt":
        os.system("cls")
    else:
        os.system("clear")

def readCommand(message : str) -> str:
    command = input(message)
    return command

def parseCommand(command : str) -> list:
    invalidCommandMessage = "Invalid command was inputed."
    positiveIntegersMessage = "The integer arguments must be positive!"

    command = command.strip()

    # Less magic constants
    token = 0
    args = 1

    commandTokens = command.split(' ', 1)
    if len(commandTokens) < 2:
        raise ValueError(invalidCommandMessage)

    commandTokens[args] = commandTokens[args].strip()

    if commandTokens[token] == 'add':
        commandTokens[args] = commandTokens[args].split(' ', 3)
        if len(commandTokens[args]) != 3:
            raise ValueError(invalidCommandMessage)
        try:
            commandTokens[args][1] = int(commandTokens[args][1])
            commandTokens[args][2] = int(commandTokens[args][2])
            if commandTokens[args][1] < 0 or commandTokens[args][2] < 0:
                raise ValueError(positiveIntegersMessage)
        except:
            raise ValueError(positiveIntegersMessage)

    elif commandTokens[token] == 'remove':
        commandTokens[args] = commandTokens[args].split(' ', 2)
        if len(commandTokens[args]) != 2:
            raise ValueError(invalidCommandMessage)
        if commandTokens[args][0] not in ["<", ">"]:
            raise ValueError(invalidCommandMessage)
        try:
            commandTokens[args][1] = int(commandTokens[args][1])
            if commandTokens[args][1] < 0:
                raise ValueError(positiveIntegersMessage)
        except:
            raise ValueError(positiveIntegersMessage)

    elif commandTokens[token] == 'list':
        commandTokens[args] = [commandTokens[args]]
        if commandTokens[args][0] not in ["price", "quantity"]:
            raise ValueError(invalidCommandMessage)

    return commandTokens

def printProductList(productList: list) -> None:
    for product in productList:
        print("Name: " + product["name"] + "\nQuantity: " + str(product["quantity"]) + "\nPrice: " + str(product["price"]) + "\n")

def start() -> None:
    clearScreen()

    products = []

    while True:
        command = readCommand("Warehouse Simulator > ")

        # Less magic constants
        token = 0
        args = 1

        try:
            command = parseCommand(command)
        except ValueError as err:
            print("\nError: " + str(err) + "\n")

        if command[token] == 'add':
            service.addProduct(products, command[args][0], command[args][1], command[args][2])
            print("\nProduct added successfully!\n")

        elif command[token] == 'list':
            if len(products) == 0:
                print("\nProduct list is empty!\n")

            elif command[args][0] == 'price':
                print("\nProducts listed by price:")
                print("-------------------------")
                service.sortByPrice(products)
                printProductList(products)

            elif command[args][0] == 'quantity':
                print("\nProducts listed by quantity:")
                print("----------------------------")
                service.sortByQuantity(products)
                printProductList(products)

        elif command[token] == 'remove':
            if command[args][0] == '<':
                service.removeLessThanPrice(products, command[args][1])
                
            elif command[args][0] == '>':
                service.removeMoreThanPrice(products, command[args][1])
            print("\nAll products that satisfy the requirement have been removed successfully!\n")