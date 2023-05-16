#
#   Note for thyself:
#   For specifications we need a description, preconditions (things to check):
#   postconditions (conditions for the result), input (+ descriptions, preconditions, postconditions if required), output (+ descriptions, preconditions if required, postconditions), exceptions (optional).
#

import ui
import functions as operations

def main():
    # Generate 10 random expenses.
    expenseList = []
    expenseHistory = []
    operations.generateRandomExpenses(expenseList, 10, expenseHistory)
    
    # Main loop of the app
    ui.start(expenseList, expenseHistory)

if __name__ == '__main__':
    main()