#
#   This module contains all implemented game objects.
#
from colorama import Fore, Back, Style
from copy import deepcopy
from texttable import Texttable

GAMEPOS_X = 0
GAMEPOS_Y = 1

ORIENTATION_NORTH = 0
ORIENTATION_EAST = 1
ORIENTATION_SOUTH = 2
ORIENTATION_WEST = 3

TILE_UNKNOWN = 0
TILE_MISSED = 1
TILE_HIT = 2
TILE_SHIP = 3

DIFFICULTY_EASY = 0
DIFFICULTY_MEDIUM = 1
DIFFICULTY_HARD = 2

DIRECTIONAL_LIST = [
    [0, 1],
    [1, 0],
    [0, -1],
    [-1, 0]
]

class Ship():
    _size : int
    _hitCount : int
    _orientation : int
    _position : list

    def __init__(self, size : int):
        self._orientation = 0
        self._hitCount = 0
        self._position = [0, 0]
        self._size = size

    @property
    def Body(self) -> list:
        result = [self._position[:]]
        for index in range(1, self._size):
            newPosition = result[index - 1][:]
            newPosition[GAMEPOS_X] += DIRECTIONAL_LIST[self._orientation][GAMEPOS_X]
            newPosition[GAMEPOS_Y] += DIRECTIONAL_LIST[self._orientation][GAMEPOS_Y]
            result.append(newPosition)
        return result

class Table():
    _ships : list
    _tableSize : list
    _tableStatus : list

    def __init__(self, size_x : int, size_y : int):
        self._tableSize = [0, 0]
        self._tableSize[GAMEPOS_X] = size_x
        self._tableSize[GAMEPOS_Y] = size_y
        self._tableStatus = []
        for index_y in range(size_y):
            self._tableStatus.append([])
            for index_x in range(size_x):
                self._tableStatus[index_y].append(TILE_UNKNOWN)
        self._ships = []

    def doShot(self, position_x : int, position_y : int) -> bool:
        if position_x < 0 or position_y < 0 or position_x > self._tableSize[GAMEPOS_X] or position_y > self._tableSize[GAMEPOS_Y]:
            raise GameException("Invalid shooting position!")
        if self._tableStatus[position_x][position_y] in [TILE_HIT, TILE_MISSED]:
            raise GameException("Position already shot!")

        if self._tableStatus[position_x][position_y] == TILE_UNKNOWN:
            self._tableStatus[position_x][position_y] = TILE_MISSED
            return False

        self._tableStatus[position_x][position_y] = TILE_HIT
        for ship in self._ships:
            if [position_x, position_y] in ship.Body:
                ship._hitCount += 1
                if ship._hitCount == ship._size:
                    # Mark everything near as missed.
                    for position in ship.Body:
                        for direction in DIRECTIONAL_LIST:
                            try:
                                self.doShot(position[GAMEPOS_X] + direction[GAMEPOS_X], position[GAMEPOS_Y] + direction[GAMEPOS_Y])
                            except:
                                pass
                    self._ships.remove(ship)
                return True

    def placeShip(self, newShip : Ship):
        self._ships.append(deepcopy(newShip))
        for position in newShip.Body:
            self._tableStatus[position[GAMEPOS_X]][position[GAMEPOS_Y]] = TILE_SHIP

    def canPlaceShip(self, whatShip : Ship) -> bool:
        for position in whatShip.Body:
            for direction in DIRECTIONAL_LIST:
                for ship in self._ships:
                    if [position[GAMEPOS_X] + direction[GAMEPOS_X], position[GAMEPOS_Y] + direction[GAMEPOS_Y]] in ship.Body:
                        return False

            if position[GAMEPOS_X] < 0 or position[GAMEPOS_Y] < 0 or position[GAMEPOS_X] >= self._tableSize[GAMEPOS_X] or position[GAMEPOS_Y] >= self._tableSize[GAMEPOS_Y]:
                return False

            if self._tableStatus[position[GAMEPOS_X]][position[GAMEPOS_Y]] not in [TILE_UNKNOWN]:
                return False

            for ship in self._ships:
                if position in ship.Body:
                    return False
        return True

    def couldPlaceShip(self, whatShip : Ship) -> bool:
        for position in whatShip.Body:
            if position[GAMEPOS_X] < 0 or position[GAMEPOS_Y] < 0 or position[GAMEPOS_X] >= self._tableSize[GAMEPOS_X] or position[GAMEPOS_Y] >= self._tableSize[GAMEPOS_Y]:
                return False

            if self._tableStatus[position[GAMEPOS_X]][position[GAMEPOS_Y]] not in [TILE_UNKNOWN, TILE_SHIP]:
                return False
        return True

    def toString(self, showShips : bool):   # pragma: nocover
        texttable = Texttable()
        CHAR_EMPTY = " "
        CHAR_MISS = u"\u22EF"
        CHAR_SHIP = u"\u2588"
        CHAR_HIT = u"\u2592"

        resultTable = [[' ']]
        for index in range(self._tableSize[GAMEPOS_Y]):
            resultTable[0].append(str(index))
        
        for ypos in range(self._tableSize[GAMEPOS_Y]):
            resultTable.append([chr(ord('A') + ypos)])
            for xpos in range(self._tableSize[GAMEPOS_X]):
                charToAppend = CHAR_EMPTY

                if showShips == True:
                    for ship in self._ships:
                        if [xpos, ypos] in ship.Body:
                            charToAppend = CHAR_SHIP

                if self._tableStatus[xpos][ypos] == TILE_HIT:
                    charToAppend = CHAR_HIT
                elif self._tableStatus[xpos][ypos] == TILE_MISSED:
                    charToAppend = CHAR_MISS
                resultTable[ypos + 1].append(charToAppend)

        texttable.add_rows(resultTable)

        return texttable.draw()

    @property
    def Size(self) -> list:
        return self._tableSize[:]

    @property
    def Table(self) -> list:
        return self._tableStatus[:]

class GameException(Exception):
    pass