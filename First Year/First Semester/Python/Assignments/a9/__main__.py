from ui.gui import *
from ui.terminal import *

import argparse

def createArgumentParser():
    parser = argparse.ArgumentParser(
        prog = "PYShips",
        description = "Open source implementation of the boardgame Battleship in Python."
    )
    parser.add_argument(
        '-t', '--terminal',
        help = "uses the terminal as the main display interface of the game",
        action = 'store_true'
    )
    parser.add_argument(
        '-g', '--gui',
        help = "uses a GUI as the main display interface of the game. Default.",
        action = 'store_true',
    )
    return parser

# Entry point.
if __name__ == "__main__":
    # Parse arguments.
    arguments = createArgumentParser().parse_args()

    # Check in what mode should the app start.
    app = None
    if arguments.gui:
        app = GUIApp()
    else:
       app = TerminalApp()

    # App main loop.
    app.start()