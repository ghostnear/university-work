from services import *
from ui import UI


def test_services():
    ui = UI()
    ui.clearScreen()
    testService = Service()

    # Force clean
    testService.repository.numberList = []

    # Valid data tests
    testService.saveComplexNumber(10, 10)
    currentList = testService.getAllNumbers()
    assert (
        len(currentList) == 1
        and currentList[0].real == 10
        and currentList[0].imaginary == 10
    ), "Complex number addition / list getting is wrong!"

    testService.saveComplexNumber(10, 10)
    testService.saveComplexNumber(10, 10)
    testService.filterInterval(1, 2)
    currentList = testService.getAllNumbers()
    assert len(currentList) == 2, "Complex number filtering is wrong!"

    print("All tests passed successfully!\n")


if __name__ == "__main__":
    test_services()
