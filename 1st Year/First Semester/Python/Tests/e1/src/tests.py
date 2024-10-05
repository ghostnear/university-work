from service import *

# 93% coverage.

if __name__ == "__main__":
    service = Service()

    assert service.checkWin() == True, "Game should be winnable at the start."

    assert service._year == 1, "Values were not initialized properly in the constructor."
    assert service._acres == 1000, "Values were not initialized properly in the constructor."
    assert service._starved == 0, "Values were not initialized properly in the constructor."
    assert service._arrived == 0, "Values were not initialized properly in the constructor."

    assert service.IsOver == False, "Game starts as a loss instantly."

    try:
        service.checkBuyable(0)
        service.checkBuyable(-100)
        service.checkBuyable(100)
    except: # pragma: nocover
        assert False, "Basic buy check fail."

    try:
        service.checkFeedable(0)
        service.checkFeedable(100)
    except: # pragma: nocover
        assert False, "Basic feed check fail."

    try:
        service.checkPlantable(0)
        service.checkPlantable(1000)
    except: # pragma: nocover
        assert False, "Basic plant check fail."

    service.simulateYear(0, 0, 0)
    assert service._starved == 100, "Instant death not working."
    assert service._population == 0, "Instant death not working."
    assert service.checkWin() == False, "Win check is wrong."

    print("\nAll tests passed successfully!\n")