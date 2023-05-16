"""
User interface for the game.
"""

import board
import game
import os

def clear_screen():
    if os.name == 'nt':
        os.system("cls")
    else:
        os.system("clear")

def process_command(user_command):
    # Remove whitespaces and dont make it capitalized.
    user_command = user_command.strip()
    user_command = user_command.lower()

    # Split into command + parameters.
    tokens = user_command.split(maxsplit = 1)

    # Split the parameters
    for i in range(len(tokens)):
        tokens[i] = tokens[i].strip()
        if i > 0:
            tokens[i] = tokens[i].split(',')

    return tokens

def clear_and_print_board(game_board):
    clear_screen()
    print(board.to_string(game_board))

def start():
    game_board = board.create()
    clear_and_print_board(game_board)

    while True:
        user_command = input("\nYour action:\n> ")
        user_command = process_command(user_command)
        if user_command[0] == 'move':
            # TODO: check argument counts
            # TODO: endgame conditions
            try:
                game.human_move(game_board, int(user_command[1][0]) - 1, int(user_command[1][1]) - 1)
                game.computer_move(game_board)

                clear_and_print_board(game_board)
            except ValueError as err:
                clear_and_print_board(game_board)
                print("\n" + str(err))
        elif user_command[0] == 'ragequit':
            print("Computer won!")
            return
        else:
            print("Invalid command!")