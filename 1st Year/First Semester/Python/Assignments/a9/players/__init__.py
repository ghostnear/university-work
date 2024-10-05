#
#   This file contains dummy implementations for all the others to follow.
#
import random
from game import *

class PlayerController():
    _table : Table

    def __init__(self, defaultTable : Table):
        self._table = deepcopy(defaultTable)

    def getShot(self, position_x : int, position_y : int) -> bool:
        try:
            return self._table.doShot(position_x, position_y)
        except GameException as error:
            raise GameException(str(error))
    
    @property
    def Lost(self) -> bool:
        return len(self._table._ships) == 0

    def processMove(self, enemy) -> None:   # pragma: nocover
        raise NotImplementedError("Default player can not hit.")

    def setUpShips(self, shipList : list) -> None:  # pragma: nocover
        raise NotImplementedError("Default player can not generate his ships.")


class AIController(PlayerController):   # pragma: nocover
    def setUpShips(self, shipList : list) -> None:
        random.seed()

        while len(shipList) != 0:
            currentShip = shipList[0]
            currentShip._position[GAMEPOS_X] = random.randint(0, self._table._tableSize[GAMEPOS_X] - 1)
            currentShip._position[GAMEPOS_Y] = random.randint(0, self._table._tableSize[GAMEPOS_Y] - 1)
            currentShip._orientation = random.randint(0, 3)
            while not self._table.canPlaceShip(currentShip):
                currentShip._position[GAMEPOS_X] = random.randint(0, self._table._tableSize[GAMEPOS_X] - 1)
                currentShip._position[GAMEPOS_Y] = random.randint(0, self._table._tableSize[GAMEPOS_Y] - 1)
                currentShip._orientation = random.randint(0, 3)
            self._table.placeShip(currentShip)
            shipList.remove(currentShip)

    def processMove(self, enemy : PlayerController) -> None:
        raise NotImplementedError("AI has not been implemented properly!")