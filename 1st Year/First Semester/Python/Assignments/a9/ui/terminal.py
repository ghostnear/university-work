#
#   This contains the terminal implementation for the UI.
#
import os
import colorama
from ui import *
from players import *
from players.ai import *
from colorama import Fore, Back, Style

defaultShips = [
    Ship(2),
    Ship(3),
    Ship(3),
    Ship(4),
    Ship(5)
]

def clearScreen() -> None:
    if os.name == "nt":
        os.system("cls")
    else:
        os.system("clear")

def readInteger(message : str = "") -> int:
    try:
        result = int(input(message))
        return result
    except:
        return 0

def waitForEnter() -> None:
    input("Press enter to continue.")

def showError(message : str) -> None:
    clearScreen()
    print(f"\n{ Fore.RED }An error has occured: { message }.\n\n{ Fore.RESET }")
    waitForEnter()

def _processPlayerMove(self, enemy) -> None:
    clearScreen()
    print(f"{ Style.BRIGHT }Your status:{ Style.RESET_ALL }\n\n{ self._table.toString(True) }\n")
    waitForEnter()

    shot = False
    while not shot:
        clearScreen()
        print(f"{ Style.BRIGHT }The enemy's status:{ Style.RESET_ALL }\n\n{ enemy._table.toString(False) }\n")

        shot = True
        try:
            position = [readInteger("X position to shoot (0 - 9): "), ord(input("Y position to shoot (A - J): "))]
        except:
            position = [-1, -1]
        if not position[GAMEPOS_X] in range(10) or not position[GAMEPOS_Y] in range(ord('A'), ord('K')):
            shot = False
        if shot:
            try:
                enemy.getShot(position[GAMEPOS_X], position[GAMEPOS_Y] - ord('A'))
            except GameException as error:
                showError(str(error))
                shot = False

    clearScreen()
    print(f"{ Style.BRIGHT }The enemy's status after the shot:{ Style.RESET_ALL }\n\n{ enemy._table.toString(False) }\n")
    waitForEnter()

class TerminalApp(UI):
    def _setupAI(self) -> AIController:
        result = None

        while result == None:
            clearScreen()
            difficulty = readInteger(f"\n{ Style.BRIGHT }What AI difficulty would you like to play against?{ Style.RESET_ALL }\n\n(0 - { Fore.GREEN }Easy{ Fore.RESET }, 1 - { Fore.YELLOW }Medium{ Fore.RESET }, 2 - { Fore.RED }Hard{ Fore.RESET }): ")
            if difficulty == DIFFICULTY_EASY:
                result = RandomAI(Table(10, 10))
            elif difficulty == DIFFICULTY_MEDIUM:
                result = HuntAI(Table(10, 10))
            elif difficulty == DIFFICULTY_HARD:
                result = ProbabilityAI(Table(10, 10))

        result.setUpShips(defaultShips[:])

        return result

    def _setupPlayer(self, message : str) -> PlayerController:
        result = PlayerController(Table(10, 10))

        clearScreen()
        print(f"\n{ message }\n")
        waitForEnter()

        for ship in defaultShips[:]:
            setUp = False
            while not setUp:
                clearScreen()
                print(f"\nCurrent status:\n\n{ result._table.toString(True) }\n")
                
                print(f"Placing ship of length { ship._size }:\n")
                try:
                    ship._position[GAMEPOS_X] = readInteger("X position (0-9): ")
                    ship._position[GAMEPOS_Y] = ord(input("Y position (A-J): ")) - ord('A')
                    ship._orientation = readInteger("Orientation\n(0 - South, 1 - East, 2 - North, 3 - West): ")
                except:
                    ship._position[GAMEPOS_X] = -1

                if ship._position[GAMEPOS_X] in range(result._table._tableSize[GAMEPOS_X]) and ship._position[GAMEPOS_Y] in range(result._table._tableSize[GAMEPOS_Y]) and ship._orientation in range(4):
                    if result._table.canPlaceShip(ship):
                        setUp = True
                    else:
                        showError("Can't place ship at the specified location!")
                else:
                    showError("Invalid ship data entered!")
            result._table.placeShip(ship)
        
        return result

    def _pvpMatch(self):
        # Pre game.
        players = [None] * 2
        players[0] = self._setupPlayer("Setting up player 1 ships!")
        players[0].processMove = _processPlayerMove
        players[1] = self._setupPlayer("Setting up player 2 ships!")
        players[1].processMove = _processPlayerMove

        # Game
        while not players[0].Lost and not players[1].Lost:
            players[0].processMove(players[0], players[1])

            print("\nPlease let player 2 at the controls.\n")
            waitForEnter()

            players[1].processMove(players[1], players[0])

            print("\nPlease let player 1 at the controls.\n")
            waitForEnter()
        
        # End game.
        clearScreen()
        if players[0].Lost == players[1].Lost:
            print(f"\n{ Style.BRIGHT }{ Fore.BLUE }Game ended as a draw!\n{ Fore.RESET }{ Style.RESET_ALL }")
        elif players[0].Lost == False:
            print(f"\n{ Style.BRIGHT }{ Fore.GREEN }Player 1 won!\n{ Fore.RESET }{ Style.RESET_ALL }")
        else:
            print(f"\n{ Style.BRIGHT }{ Fore.GREEN }Player 2 won!\n{ Fore.RESET }{ Style.RESET_ALL }")
        waitForEnter()

    def _aiMatch(self):
        # Pre game.
        players = [None] * 2
        players[1] = self._setupAI()
        players[0] = self._setupPlayer("Setting up the player's ships!")
        players[0].processMove = _processPlayerMove

        # Game
        while not players[0].Lost and not players[1].Lost:
            players[0].processMove(players[0], players[1])
            try:
                players[1].processMove(players[0])
            except GameException as error:
                showError(str(error))
        
        # End game.
        clearScreen()
        if players[0].Lost == players[1].Lost:
            print(f"\n{ Style.BRIGHT }{ Fore.BLUE }Game ended as a draw!\n{ Fore.RESET }{ Style.RESET_ALL }")
        elif players[0].Lost == False:
            print(f"\n{ Style.BRIGHT }{ Fore.GREEN }Player won!\n{ Fore.RESET }{ Style.RESET_ALL }")
        else:
            print(f"\n{ Style.BRIGHT }{ Fore.RED }AI won!\n{ Fore.RESET }{ Style.RESET_ALL }")
        waitForEnter()

    def _displayMenu(self) -> None:
        clearScreen()
        pyShipsString = "██████╗ ██╗   ██╗███████╗██╗  ██╗██╗██████╗ ███████╗\n██╔══██╗╚██╗ ██╔╝██╔════╝██║  ██║██║██╔══██╗██╔════╝\n██████╔╝ ╚████╔╝ ███████╗███████║██║██████╔╝███████╗\n██╔═══╝   ╚██╔╝  ╚════██║██╔══██║██║██╔═══╝ ╚════██║\n██║        ██║   ███████║██║  ██║██║██║     ███████║\n╚═╝        ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝╚═╝     ╚══════╝"
        print(f"\n{ Fore.GREEN }{ pyShipsString }{ Fore.RESET }\n\nChoose your gamemode:\n\n{ Style.BRIGHT }1. Player vs Player.\n2. Player vs A.I.\n3. Exit.\n{ Style.RESET_ALL }")

    def start(self) -> None:
        running = True
        colorama.init()
        while running:
            self._displayMenu()
            option = readInteger("Action > ")

            # Exit
            if option == 1:
                self._pvpMatch()
            elif option == 2:
                self._aiMatch()
            elif option == 3:
                running = False
            else:
                showError("Unknown action selected")

        clearScreen()
        print(f"\n{ Fore.GREEN }Bye!{ Fore.RESET }\n")