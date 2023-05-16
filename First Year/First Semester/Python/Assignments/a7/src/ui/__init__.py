#
#   UI implementation.
#

import os
from services import Service


class UI:
    running: bool = True
    state: str = "menu"
    backend: Service = Service()

    def waitForEnter(self, message: str) -> None:
        input(message)

    def clearScreen(self) -> None:
        if os.name == "nt":
            os.system("cls")
        else:
            os.system("clear")

    def readInteger(self, message: str) -> int:
        result = None
        try:
            result = int(input(message))
        except:
            raise ValueError("Not an integer.")
        return result

    def parseComplexForm(self, message: str) -> tuple:
        try:
            # Number represented using Python's complex numbers to make the parsing easier.
            internalNumber = complex(message.replace("i", "j").replace(" ", ""))
        except:
            raise ValueError("Invalid complex number inputed!")

        # Return to use with our own ComplexNumber class.
        return (internalNumber.real, internalNumber.imag)

    def printError(self, error: str) -> None:
        self.clearScreen()
        self.waitForEnter("\n" + error + "\n\nPress enter to continue...")

    def printMenu(self) -> None:
        self.clearScreen()
        print("\nWelcome to the Complex Number Simulator!")
        print("----------------------------------------\n")
        print("1. Add a number to the list.")
        print("2. Display the number list.")
        print("3. Filter the list to keep only the numbers between 2 indices.")
        print("4. Undo the last operation.")
        print("5. Exit the app.\n")

    def start(self) -> None:
        """
        Executes the main loop of the app.
        """
        while self.running:
            self.printMenu()
            try:
                match self.readInteger("> "):

                    case 1:
                        try:
                            self.clearScreen()
                            resutingNumber = self.parseComplexForm(input("\nInput a complex number (in the a + bi) form: "))
                            self.backend.saveComplexNumber(resutingNumber[0], resutingNumber[1])

                            self.clearScreen()
                            print("\nComplex number successfully added to the list!")
                            self.waitForEnter("\nPress enter to continue...")
                        except ValueError as err:
                            self.printError(str(err))

                    case 2:
                        self.clearScreen()
                        numberList = self.backend.getAllNumbers()
                        if len(numberList) == 0:
                            print("\nThere are no numbers in the list! Maybe try to add some?")
                        else:
                            print("\nThe following numbers are stored in the list:\n")
                            for number in numberList:
                                print(str(number))
                        self.waitForEnter("\nPress enter to continue...")

                    case 3:
                        self.clearScreen()
                        try:
                            leftSide = self.readInteger("\nInput an integer for the left side of the interval: ")
                            rightSide = self.readInteger("\nInput an integer for the right side of the interval: ")

                            self.backend.filterInterval(leftSide, rightSide)

                            self.clearScreen()
                            print("\nFilter applied successfully to the list!")
                            self.waitForEnter("\nPress enter to continue...")
                        except IndexError as err:
                            self.printError(str(err))
                        except ValueError as err:
                            self.printError(str(err))
                    case 4:
                        self.clearScreen()
                        try:
                            self.backend.undo()

                            self.clearScreen()
                            print("\nUndid last operation successfully!")
                            self.waitForEnter("\nPress enter to continue...")
                        except IndexError as err:
                            self.printError(str(err))

                    case 5:
                        self.running = False

                    case other:
                        self.printError("Invalid operation chosen!")
                        
            except ValueError as err:
                self.printError(str(err))

        self.clearScreen()
        print("\nBye!\n")


def createAppInstance():
    return UI()
