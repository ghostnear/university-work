#
#   UI stuff here.
#
import os
from src.services import *

def clearScreen():
    if os.name == "nt":
        os.system("cls")
    else:
        os.system("clear")

def readInteger(message : str = ""):
    try:
        result = int(input(message))
        return result
    except:
        raise ValueError("The input is not an integer.")

def waitForEnter():
    input("\nPress enter to continue.")

def printError(message : str):
    clearScreen()
    print(f"An error occured:\n\n{ message }\n")
    waitForEnter()

class UI:
    _service : AssignmentService

    def __init__(self):
        try:
            self._service = AssignmentService()
        except ServiceError as error:
            print(f"{ str(error) }")

    def _printMenu(self):
        print("Assignment Checker\n")
        print("1. Add an assignment.")
        print("2. Display all assignments.")
        print("3. Dishonesty check.")
        print("4. Exit.\n")

    def start(self):
        running = True
        while running:
            clearScreen()
            self._printMenu()
            result = 0
            try:
                result = readInteger("Action > ")
            except ValueError as error:
                printError(str(error))

            match result:
                case 1: # Assignment adding.
                    clearScreen()
                    try:
                        newID = readInteger("Assignment ID (unique integer):\n")
                        newName = input("Student name (string, at least 3 characters):\n")
                        newSolution = input("Solution (nonempty string):\n")
                        self._service.addAssigment(newID, newName, newSolution)
                    except ServiceError as error:
                        printError(str(error))
                    except ValueError:
                        printError("Assignment ID must be an integer!")
                
                case 2: # Assignment display.
                    clearScreen()
                    for assignment in self._service.getAssignments():
                        print(f"{ assignment }\n")
                    waitForEnter()

                case 3: # Dishonesty check.
                    clearScreen()
                    results = self._service.reportHonesty()

                    if len(results) == 0:
                        print("The students are honest.")
                    else:
                        print("These students look dishonest:\n")
                        for result in results:
                            print(result)

                    waitForEnter()

                case 4: # Exit
                    running = False
        
        clearScreen()
        print("\nBye!\n")
            
