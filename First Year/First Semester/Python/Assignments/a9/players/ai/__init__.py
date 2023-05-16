import random
from copy import deepcopy
from game import *
from players import AIController

#
#   This AI implementation uses the 'hunt' implementation.
#   That means that after each hit, it seeks to find the actual shape of the ship by only targeting nearby positions.
#
class HuntAI(AIController):
    _hitQueue : list

    def __init__(self, defaultTable : Table):
        super().__init__(defaultTable)
        self._hitQueue = []

    def processMove(self, enemy) -> None:
        random.seed()
        if len(self._hitQueue) == 0:
            moved = False
            while not moved:
                position = [random.randrange(0, enemy._table.Size[GAMEPOS_X]), random.randrange(0, enemy._table.Size[GAMEPOS_Y])]
                if enemy._table._tableStatus[position[GAMEPOS_X]][position[GAMEPOS_Y]] not in [TILE_HIT, TILE_MISSED]:
                    if enemy.getShot(position[GAMEPOS_X], position[GAMEPOS_Y]) == True:
                        for direction in DIRECTIONAL_LIST:
                            newPosition = [position[GAMEPOS_X] + direction[GAMEPOS_X], position[GAMEPOS_Y] + direction[GAMEPOS_Y]]
                            if newPosition[GAMEPOS_X] in range(enemy._table.Size[GAMEPOS_X]) and newPosition[GAMEPOS_Y] in range(enemy._table.Size[GAMEPOS_Y]) and enemy._table.Table[newPosition[GAMEPOS_X]][newPosition[GAMEPOS_Y]] in [TILE_UNKNOWN, TILE_SHIP]:
                                self._hitQueue.insert(0, newPosition[:])
                    moved = True
        else:
            moved = False
            while not moved:
                try:
                    enemy.getShot(self._hitQueue[0][GAMEPOS_X], self._hitQueue[0][GAMEPOS_Y])
                    for direction in DIRECTIONAL_LIST:
                        newPosition = [self._hitQueue[0][GAMEPOS_X] + direction[GAMEPOS_X], self._hitQueue[0][GAMEPOS_Y] + direction[GAMEPOS_Y]]
                        if newPosition[GAMEPOS_X] in range(enemy._table.Size[GAMEPOS_X]) and newPosition[GAMEPOS_Y] in range(enemy._table.Size[GAMEPOS_Y]) and enemy._table.Table[newPosition[GAMEPOS_X]][newPosition[GAMEPOS_Y]] in [TILE_UNKNOWN, TILE_SHIP]:
                            self._hitQueue.insert(0, newPosition[:])
                    moved = True
                except:
                    pass
                self._hitQueue.pop(0)
            if not moved:
                self.processMove(enemy) # retry

#
#   The most complex, this AI uses the probabilistic aproach by matching all of the ships on the table.
#   After that, it shoots the best spot out of all of them. If there are more of them, it chooses randomly between them.
#
class ProbabilityAI(AIController):
    _heatmap : list

    def processMove(self, enemy) -> None:
        random.seed()
        self._heatmap = []
        for row in range(enemy._table.Size[GAMEPOS_X]):
            result = []
            for col in range(enemy._table.Size[GAMEPOS_Y]):
                result.append(0)
            self._heatmap.append(result[:])

        # Build heatmap
        for ship in deepcopy(enemy._table._ships):
            for position_x in range(self._table.Size[GAMEPOS_X]):
                for position_y in range(self._table.Size[GAMEPOS_Y]):
                    if self._table.Table[position_x][position_y] == TILE_HIT:
                        for orientation in range(4):
                            ship._position = [position_x, position_y]
                            ship._orientation = orientation
                            if self._table.couldPlaceShip(ship):
                                for position in ship.Body:
                                    self._heatmap[position_x][position_y] += 1

        # Get max heat position that has not been shot.
        maxHeat = -1
        maxPosition = []
        for position_x in range(enemy._table.Size[GAMEPOS_X]):
            for position_y in range(enemy._table.Size[GAMEPOS_Y]):
                if enemy._table.Table[position_x][position_y] not in [TILE_MISSED, TILE_HIT]:
                    if self._heatmap[position_x][position_y] > maxHeat:
                        maxHeat = self._heatmap[position_x][position_y]
                        maxPosition = [[position_x, position_y]]
                    elif self._heatmap[position_x][position_y] == maxHeat:
                        maxPosition.append([position_x, position_y])

        # Shoot
        shot = False
        while not shot:
            try:
                enemy.getShot(random.choice(maxPosition)[GAMEPOS_X], random.choice(maxPosition)[GAMEPOS_Y])
                shot = True
            except:
                pass

#
#   This AI implementation does random shooting.
#
class RandomAI(AIController):
    def processMove(self, enemy) -> None:
        random.seed()
        moved = False
        while not moved:
            position = [random.randint(0, enemy._table.Size[GAMEPOS_X] - 1), random.randint(0, enemy._table.Size[GAMEPOS_Y] - 1)]
            if enemy._table._tableStatus[position[GAMEPOS_X]][position[GAMEPOS_Y]] not in [TILE_HIT, TILE_MISSED]:
                enemy.getShot(position[GAMEPOS_X], position[GAMEPOS_Y])
                moved = True