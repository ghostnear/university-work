import os
from service import *

def clearScreen() -> None:
    """
        Clears the screen.
    """
    if os.name == "nt":
        os.system("cls")
    else:
        os.system("clear")

def readInteger(message : str) -> int:
    """
        Reads an integer from the keyboard.
            - message (str) - The message to be shown.

        Returns:
            - int - The integer read from the keyboard.

        Eventual errors:
            - ValueError - If the value is not an integer.
    """
    try:
        result = int(input(message))
        return result
    except:
        raise ValueError("Not an integer.")

def waitForEnter():
    input("Press enter to continue.")

def printError(message : str) -> None:
    """
        Prints an error to the screen.
            - message (str) - The message to be shown.
    """
    clearScreen()
    print(f"\n\nAn error occured: { message }\n\n")
    waitForEnter()

class UI:
    _service : Service = Service()

    def start(self):
        """
            Starts the main loop of the app.
        """
        # Simulate the 5 year plan.
        for _ in range(4):
            ended = False
            while not ended:
                gotInput = False
                acresToBuy = 0
                unitsToFeed = 0
                acresToPlant = 0

                while not gotInput:
                    try:
                        clearScreen()
                        print(f"Your advisor has informed you:\n\n{ self._service }\n")
                        acresToBuy = readInteger("Acres to buy / sell (integer, + / -) > ")
                        unitsToFeed = readInteger("Units to feed the population (integer) > ")
                        acresToPlant = readInteger("Acres to plant > ")
                        gotInput = True
                    except ValueError as err:
                        printError(str(err))
                        gotInput = False
                        
                try:
                    self._service.simulateYear(acresToBuy, unitsToFeed, acresToPlant)
                    ended = True
                except ValueError as err:
                    printError(str(err))

                if self._service.IsOver:
                    clearScreen()
                    print(f"Your advisor has informed you:\n\n{ self._service }\n")
                    print(f"GAME OVER. Your advisor is incredibly dissappointed in you. Your city died by year { self._service._year }.\n")
                    exit(0)

        clearScreen()
        print(f"Your advisor has informed you:\n\n{ self._service }\n")

        if self._service.checkWin():
            print("Game over. Your advisor is proud of you, you did well.\n")
        else:
            print("GAME OVER. Your advisor is dissappointed of you, you did not do well.\n")