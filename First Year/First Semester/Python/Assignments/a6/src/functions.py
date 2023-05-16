#
#   The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements.
#   Functions here communicate via function parameters, the return statement and raising of exceptions. 
#

import random

def createExpense(appartmentNumber : int, transactionType : str, ammountPaid : int):
    """
    Requirements:
    
        appartmentNumber {int} -- Positive, non-zero value.

        transactionType {str} -- One of "water", "heating", "electricity", "gas", "other".

        ammountPaid {int} -- Positive, non-zero value.

    Possible errors:

        ValueError when any of the requirements are not met.
    """
    expense = {}
    setExpenseAppartment(expense, appartmentNumber)
    setExpensePaidAmmount(expense, ammountPaid)
    setExpenseType(expense, transactionType)
    return expense

#
#   Generators
#

def generateRandomByte():
    return random.randint(0, 255)

def generateRandomExpenseType():
    return random.choice(["water", "heating", "electricity", "gas", "other"])

def generateRandomExpenses(expenseList : list, count : int, expenseHistory : list):
    for index in range(count):
        addExpense(expenseList, generateRandomByte(), generateRandomExpenseType(), generateRandomByte(), expenseHistory)

def filterExpenses(expenseList: list, appliedFunction):
    """
        Applies a function to the specified list to filter elements.

    Returns:
        A list with all the filtered elements.
    """
    return list(filter(appliedFunction, expenseList))

def addExpense(expenseList : list, appartmentNumber : int, transactionType : str, ammountPaid : int, expenseHistory : list):
    expense = createExpense(appartmentNumber, transactionType, ammountPaid)
    expenseHistory.append(expenseList[:])
    expenseList.append(expense)

#
#   Getters and setters...
#

def getExpenseAppartment(expense):
    return expense["appartment"]

def setExpenseAppartment(expense, value : int):
    if value <= 0:
        raise ValueError("Appartment must be a positive non-zero value.")
    expense["appartment"] = value

def getExpensePaidAmmount(expense):
    return expense["ammount"]

def setExpensePaidAmmount(expense, ammount : int):
    if ammount <= 0:
        raise ValueError("Ammount paid must be a positive non-zero value.")
    expense["ammount"] = ammount

def getExpenseType(expense):
    return expense["type"]

def setExpenseType(expense, expenseType : str):
    if not expenseType in ["water", "heating", "electricity", "gas", "other"]:
        raise ValueError("Unknwon expense type.")
    expense["type"] = expenseType

#
#   Tests! Yay!
#

def test_expense():
    expenses = []
    expenseHistory = []

    # Correct adding
    addExpense(expenses, 53, "other", 69, expenseHistory)
    assert getExpenseAppartment(expenses[0]) == 53, "Incorrect values after adding!"
    assert getExpensePaidAmmount(expenses[0]) == 69, "Incorrect values after adding!"
    assert getExpenseType(expenses[0]) == "other", "Incorrect values after adding!"

    # Incorrect addings
    try:
        addExpense(expenses, -1, "other", 69, expenseHistory)
        assert False, "Didn't throw an exception when using a negative value for appartment."
    except ValueError as error:
        assert True
    try:
        addExpense(expenses, 69, "other", -1, expenseHistory)
        assert False, "Didn't throw an exception when using a negative value for ammount."
    except ValueError as error:
        assert True
    try:
        addExpense(expenses, 53, "food", 69, expenseHistory)
        assert False, "Didn't throw an exception when using a wrong type."
    except ValueError as error:
        assert True

    # Filters with results
    assert filterExpenses(expenses, None) != [], "This should filter all of the expenses but it does not."
    assert filterExpenses(expenses, lambda expense: getExpenseType(expense) == 'other') != [], "This should filter one of the expenses but it does not."
    assert filterExpenses(expenses, lambda expense: getExpenseAppartment(expense) == 53) != [], "This should filter one of the expenses but it does not."
    assert filterExpenses(expenses, lambda expense: getExpensePaidAmmount(expense) == 69) != [], "This should filter one of the expenses but it does not."
    
    # Filters with no results
    assert filterExpenses(expenses, lambda expense: getExpenseType(expense) == 'idk') == [], "This should filter none of the expenses but it does not."
    assert filterExpenses(expenses, lambda expense: getExpenseAppartment(expense) == 10) == [], "This should filter none of the expenses but it does not."
    assert filterExpenses(expenses, lambda expense: getExpensePaidAmmount(expense) == 30) == [], "This should filter none of the expenses but it does not."

    print("All expenses tests successful!")

if __name__ == '__main__':
    test_expense()