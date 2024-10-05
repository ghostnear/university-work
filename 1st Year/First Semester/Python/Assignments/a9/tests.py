from game import *
from players import *

# 95% test coverage.
def doTests():
    player = PlayerController(Table(10, 10))

    assert player._table.Size == [10, 10], "Size not set up properly."

    ship = Ship(2)
    ship._position = [0, 0]
    ship._orientation = 0

    assert player._table.canPlaceShip(ship) == True, "Ship placing check with vision wrong."
    assert player._table.couldPlaceShip(ship) == True, "Ship placing check with no vision wrong."

    player._table.placeShip(ship)
    assert player._table.canPlaceShip(ship) == False, "Ship placing check with vision wrong."

    assert player._table._tableStatus[ship.Body[0][GAMEPOS_X]][ship.Body[0][GAMEPOS_Y]] == TILE_SHIP, "Ship placing wrong."

    assert player.Lost == False, "Win check wrong."
    player.getShot(0, 0)
    player.getShot(0, 1)
    assert player.Lost == True, "Win check wrong."

    try:
        player.getShot(0, 0)
        assert False, "Shooting checks wrong."  # pragma: nocover
    except:
        pass

if __name__ == "__main__":
    doTests()