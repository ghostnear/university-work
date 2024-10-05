"""
    This module handles the game's board.
"""

import texttable

def create():
    """
    Creates a Tic-Tac-Toe board.

    Returns:
        game_board: The new board.
    """    
    board = []
    for _ in range(3):
        board.append([' ', ' ', ' '])
    return board

def get_symbol(game_board, row, col):
    """
    Get the symbol from a position on the board.

    Arguments:
        game_board: The board of the game.
        row: One of [0, 1, 2].
        column: One of [0, 1, 2].

    Returns: None
    """    

    # TODO: handle wrong inputs.
    return game_board[row][col]

def make_move(game_board, row, column, symbol):
    """
    Record a move on the game board.

    Args:
        game_board: The board of the game.
        row: One of [0, 1, 2].
        column: One of [0, 1, 2].
        symbol: One of 'X' or 'O'.
    
    Returns: None

    Raises ValueError if symbol is not appropriate, move is outside the board or the square is already taken.
    """
    # Check if the move is inside the board.
    if row > 2 or row < 0 or column > 2 or column < 0:
        raise ValueError("Move outside the board!")

    # Check if place is not already written.
    if game_board[row][column] != ' ':
        raise ValueError("Move can't overwrite an already placed symbol!")

    # Check if the symbol is valid.
    if symbol not in ['X', 'O']:
        raise ValueError("Move value can only have values in the list ['X', 'O']!")

    # Do the move.
    game_board[row][column] = symbol

def to_string(game_board):
    """
    Converts the table to a printable string.

    Arguments:
        game_board: The board of the game.

    Returns:
        string - The board as a string.
    """      
    table = texttable.Texttable()
    for row in range(3):
        table.add_row(game_board[row])
    return table.draw()

def test_make_move():
    b = create()

    # Test that the row is empty
    for row in range(3):
        for col in range(3):
            assert get_symbol(b, row, col) == ' '

    # Make some moves on the board
    make_move(b, 0, 0, 'X')
    assert get_symbol(b, 0, 0) == 'X'

    make_move(b, 2, 2, 'O')
    assert get_symbol(b, 2, 2) == 'O'

    # Check for errors
    try:
        make_move(b, 4, 4, 'X')
        assert False, "Excapetion was not raised for being outside the bounds!"
    except ValueError:
        pass

    try:
        make_move(b, 0, 2, 'Y')
        assert False, "Excapetion was not raised for wrong symbol!"
    except ValueError:
        pass

    try:
        make_move(b, 0, 0, 'X')
        assert False, "Excapetion was not raised for overwrite!"
    except ValueError:
        pass

# Do tests if main.
if __name__ == '__main__':
    test_make_move()