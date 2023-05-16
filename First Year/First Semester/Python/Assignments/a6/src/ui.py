#
#   This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#

import os
from functions import *

def readCommand():
    return input("Apartment Building Administrator Simulator > ")

def clearScreen():
    # Windows way.
    if os.name == "nt":
        os.system("cls")
    # Literally anything else.
    else:
        os.system("clear")

def displayAllExpenses(expenseList : list, message : str, format : str):
    if len(expenseList) == 0:
        print("\nThere have been no expenses registered yet!\n")
    else:
        print(f"\n{ message }")
        print("----------------------------------------")
        for expense in expenseList:
            if format == 'all':
                print(f"Appartment { getExpenseAppartment(expense) } spent { getExpensePaidAmmount(expense) } RON on { getExpenseType(expense) }.")
            elif format == 'no-appartment':
                print(f"Spent { getExpensePaidAmmount(expense) } RON on { getExpenseType(expense) }.")
        print("----------------------------------------\n")

def parseCommand(command : str):
    """
    Arguments:

        command {str} -- A command in the correct format.

    Returns:

        A list of the parsed tokens in the format of the specified command.
    
    Possible errors:

        ValueError when the command could not have been parsed properly.
    """
    command = command.strip().lower()

    # Split into the command + parameters format.
    parsedTokens = command.split(maxsplit = 1)

    # Syntax checking for all the commands.
    
    # Add command
    if parsedTokens[0] == 'add':
        # Not a singular token
        if len(parsedTokens) == 1:
            raise ValueError("Incorrect command format!")

        # Parse the arguments specifically for this command type.
        parsedTokens[1] = parsedTokens[1].split(" ", maxsplit = 3)
        if len(parsedTokens[1]) != 3:
            raise ValueError("Incorrect command format!")
        
        # Try to convert the arguments to the correct types.
        try:
            parsedTokens[1][0] = int(parsedTokens[1][0])
        except:
            raise ValueError("Appartment must be a number!")

        try:
            parsedTokens[1][2] = int(parsedTokens[1][2])
        except:
            raise ValueError("Ammount must be a number!")

    # Remove command
    elif parsedTokens[0] == 'remove':
        # Not a singular token
        if len(parsedTokens) == 1:
            raise ValueError("Incorrect command format!")

        # Parse the arguments specifically for this command type.
        parsedTokens[1] = parsedTokens[1].split(" ", maxsplit = 3)
        if len(parsedTokens[1]) == 1:
            # Try to convert the argument to integer.
            try:
                parsedTokens[1][0] = int(parsedTokens[1][0])
            except:
                # It can be a string so we'll let it pass if so.
                pass
        elif len(parsedTokens[1]) == 3:
            # Try to convert the arguments to integers.
            try:
                parsedTokens[1][0] = int(parsedTokens[1][0])
                parsedTokens[1][2] = int(parsedTokens[1][2])
            except:
                raise ValueError("The ends of the removed interval must be integers!")

            if parsedTokens[1][1] != "to":
                raise ValueError("Incorrect command format!")
        else:
            raise ValueError("Incorrect command format!")

    # Replace command
    elif parsedTokens[0] == 'replace':
        # Not a singular token
        if len(parsedTokens) == 1:
            raise ValueError("Incorrect command format!")

        # Can have only 4 arguments
        parsedTokens[1] = parsedTokens[1].split(" ", maxsplit = 4)
        if len(parsedTokens[1]) != 4:
            raise ValueError("Incorrect command format!")

        # Try to convert the arguments to integers.
        try:
            parsedTokens[1][0] = int(parsedTokens[1][0])
            parsedTokens[1][3] = int(parsedTokens[1][3])
        except:
            raise ValueError("All values must be integers!")

        if parsedTokens[1][2] != "with":
            raise ValueError("Incorrect command format!")

    # List command
    elif parsedTokens[0] == 'list':
        if len(parsedTokens) > 1:
            # Parse the arguments specifically for this command type.
            parsedTokens[1] = parsedTokens[1].split(" ", maxsplit = 2)
            if len(parsedTokens[1]) == 1:
                # Try to convert the arguments to integers.
                try:
                    parsedTokens[1][0] = int(parsedTokens[1][0])
                except:
                    raise ValueError("Appartment value must be an integer!")
            elif len(parsedTokens[1]) == 2:
                # Try to convert the arguments to integers.
                try:
                    parsedTokens[1][1] = int(parsedTokens[1][1])
                except:
                    raise ValueError("Ammount value must be an integer!")

                if not parsedTokens[1][0] in ['>', '<', '=']:
                    raise ValueError("Condition value must be from the following list: ['>', '<', '=']!")

            elif len(parsedTokens[1]) > 2:
                raise ValueError("Incorrect command format!")
    # Filter command
    elif parsedTokens[0] == 'filter':
        # Can have one argument of any type, but try to set it accordingly.
        try:
            parsedTokens[1] = [int(parsedTokens[1])]
        except:
            parsedTokens[1] = [parsedTokens[1]]

        if len(parsedTokens) != 2:
            raise ValueError("Incorrect command format!")

    # One keyword commands
    elif parsedTokens[0] == 'exit' or parsedTokens[0] == 'clear' or parsedTokens[0] == 'undo':
        # These commands should not have arguments.
        if len(parsedTokens) != 1:
            raise ValueError("Incorrect command format!")
    else:
        raise ValueError("Unknown command!")

    return parsedTokens

def start(expenseList : list, expenseHistory : list):
    while True:
        inputCommand = readCommand()
        try:
            # Parse the command into command + parameters format.
            parsedCommand = parseCommand(inputCommand)
            match parsedCommand[0]:
                # Add the expense to the expenses list.
                case 'add':
                    addExpense(expenseList, parsedCommand[1][0], parsedCommand[1][1], parsedCommand[1][2], expenseHistory)

                # Removes expenses.
                case 'remove':
                    # Only one argument.
                    if len(parsedCommand[1]) == 1:
                        # Remove all for the specified appartment.
                        if type(parsedCommand[1][0]) == int:
                            expenseHistory.append(expenseList[:])
                            expenseList = filterExpenses(expenseList, lambda expense: getExpenseAppartment(expense) != parsedCommand[1][0])
                            print(f"\nRemoved all expenses for appartment { parsedCommand[1][0] }!\n")
                        else:
                            if not parsedCommand[1][0] in ["water", "heating", "electricity", "gas", "other"]:
                                raise ValueError("Unknown expense type.")
                            expenseHistory.append(expenseList[:])
                            expenseList = filterExpenses(expenseList, lambda expense: getExpenseType(expense) != parsedCommand[1][0])
                            print(f"\nRemoved all { parsedCommand[1][0] } expenses!\n")
                    # Remove interval.
                    else:
                        expenseHistory.append(expenseList[:])
                        expenseList = filterExpenses(expenseList, lambda expense: getExpenseAppartment(expense) <= parsedCommand[1][0] or getExpenseAppartment(expense) >= parsedCommand[1][2])
                        print(f"\nRemoved all expenses for appartments { parsedCommand[1][0] } to { parsedCommand[1][2] }!\n")

                # Replace an expense.
                case 'replace':
                    expenseHistory.append(expenseList[:])
                    for expense in expenseList:
                        if getExpenseAppartment(expense) == parsedCommand[1][0] and getExpenseType(expense) == parsedCommand[1][1]:
                            setExpensePaidAmmount(parsedCommand[1][3])
                    print("\nReplacement successful!\n")

                # List all the expenses.
                case 'list':
                    # No arguments, list all expenses.
                    if len(parsedCommand) == 1:
                        displayAllExpenses(expenseList, "Displaying all expenses chronologically:", 'all')
                        
                    # One argument, list all expenses for the appartment.
                    elif len(parsedCommand[1]) == 1:
                        results = filterExpenses(expenseList, lambda expense: getExpenseAppartment(expense) == parsedCommand[1][0])
                        displayAllExpenses(results, f"Displaying all expenses of appartment { parsedCommand[1][0] } chronologically:", 'no-appartment')

                    # Two arguments, list depending on query.
                    elif len(parsedCommand[1]) == 2:
                        results = []
                        if parsedCommand[1][0] == '=':
                            results = filterExpenses(expenseList, lambda expense: getExpensePaidAmmount(expense) == parsedCommand[1][1])
                        elif parsedCommand[1][0] == '>':
                            results = filterExpenses(expenseList, lambda expense: getExpensePaidAmmount(expense) > parsedCommand[1][1])
                        elif parsedCommand[1][0] == '<':
                            results = filterExpenses(expenseList, lambda expense: getExpensePaidAmmount(expense) < parsedCommand[1][1])
                        displayAllExpenses(results, f"Displaying all expenses using the specified querry:", 'all')

                # Filter the expenses.
                case 'filter':
                    # Keep only the ones with a smaller ammount than the specified one.
                    if type(parsedCommand[1][0]) == int:
                        expenseHistory.append(expenseList[:])
                        expenseList = filterExpenses(expenseList, lambda expense: getExpensePaidAmmount(expense) < parsedCommand[1][0])
                    # Keep only the ones with a specified type.
                    else:
                        if not parsedCommand[1][0] in ["water", "heating", "electricity", "gas", "other"]:
                            raise ValueError("Unknown expense type.")
                        expenseHistory.append(expenseList[:])
                        expenseList = filterExpenses(expenseList, lambda expense: getExpenseType(expense) == parsedCommand[1][0])
                    print(f"\nFiltered { len(expenseList) } values.\n")

                # Undo last operation
                case 'undo':
                    if len(expenseHistory) == 0:
                        raise ValueError("Expense operations history is empty!")
                    expenseList = expenseHistory.pop()

                # Clear the screen
                case 'clear':
                    clearScreen()

                # Exit the app
                case 'exit':
                    break

        except ValueError as err:
            print("An error occured while executing your command:\n  " + str(err))