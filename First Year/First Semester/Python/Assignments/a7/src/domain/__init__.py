import os
import random
import pickle
import json
import json_fix  # Fixes JSON serializing for custom classes.

#
#   Complex number class and all its methods.
#


class ComplexNumber:
    real: float = 0
    imaginary: float = 0

    def __init__(self, realPart: float = 0, imaginaryPart: float = 0):
        self.real = realPart
        self.imaginary = imaginaryPart

    def __json__(self) -> str:
        return json.dumps({"real": self.real, "imaginary": self.imaginary})

    def decode(self, string : str):
        numberAsDictionary = json.loads(json.loads(string))
        self = ComplexNumber(numberAsDictionary["real"], numberAsDictionary["imaginary"])
        return self

    def __str__(self) -> str:
        resultString = str(self.real)
        if self.imaginary < 0:
            resultString += " - " + str(-self.imaginary) + " i"
        elif self.imaginary > 0:
            resultString += " + " + str(self.imaginary) + " i"
        return resultString


def complexNumberFromString(message: str) -> ComplexNumber:
    try:
        # Number represented using Python's complex numbers to make the parsing easier.
        internalNumber = complex(message.replace("i", "j").replace(" ", ""))
    except:
        raise ValueError("Invalid complex number inputed!")

    # Return to use with our own ComplexNumber class.
    return ComplexNumber(internalNumber.real, internalNumber.imag)


def generateRandomSubunitary() -> float:
    return (random.random() - 0.5) * 2


def generateRandomComplexNumber(realUpper: float, imaginaryUpper: float) -> ComplexNumber:
    return ComplexNumber(
        round(generateRandomSubunitary() * realUpper, 4),
        round(generateRandomSubunitary() * imaginaryUpper, 4),
    )


#
#   Repository base class and all its methods and subclasses.
#
class RepositoryBase:
    history: list = []
    numberList: list = []

    def __init__(self):
        for _ in range(10):
            self.numberList.append(generateRandomComplexNumber(100, 100))

    def updateHistory(self) -> None:
        self.history.append(self.getAsList()[:])

    def undo(self) -> None:
        if len(self.history) == 0:
            raise IndexError("There have been no operations made!")

        currentList = self.history.pop()
        self.saveFromList(currentList)

    # Dummy functions
    def saveComplexNumber(self, value: ComplexNumber) -> None:
        raise NotImplementedError()

    def saveFromList(self, values: list) -> None:
        raise NotImplementedError()

    def getAsList(self) -> list:
        return self.numberList


class FileRepositoryBase(RepositoryBase):
    fileLocation: str = ""

    def saveComplexNumber(self, value: ComplexNumber) -> None:
        self.numberList.append(value)
        self.writeToFile()

    def saveFromList(self, values: list) -> None:
        self.numberList = values
        self.writeToFile()


class MemoryRepository(RepositoryBase):
    def saveComplexNumber(self, value: ComplexNumber) -> None:
        self.numberList.append(value)

    def saveFromList(self, values: list) -> None:
        self.numberList = values


class TextFileRepository(FileRepositoryBase):
    # Constructor that reads from a file at the specified path.
    def __init__(self, filePath: str):
        self.fileLocation = filePath

        # File exists, load from it
        if os.path.exists(filePath):
            with open(filePath, "r") as file:
                self.numberList = []
                for textLine in file.readlines():
                    try:
                        self.numberList.append(complexNumberFromString(textLine))
                    except:
                        # Ignore invalid numbers.
                        pass
                file.close()

        # Use the already generated from memory and save the file.
        else:
            self.writeToFile()

    # Save the current state to file.
    def writeToFile(self) -> None:
        with open(self.fileLocation, "w") as file:
            for number in self.numberList:
                file.write(str(number) + "\n")
            file.close()


class BinaryFileRepository(FileRepositoryBase):
    # Constructor that reads from a file at the specified path.
    def __init__(self, filePath: str):
        self.fileLocation = filePath

        # File exists, load from it
        if os.path.exists(filePath):
            try:
                with open(filePath, "rb") as file:
                    self.numberList = pickle.load(file)
                    file.close()
            except:
                # Delete file as it is invalid and write the new numbers to the file.
                os.remove(filePath)
                self.writeToFile()

        # Use the already generated from memory and save the file.
        else:
            self.writeToFile()

    # Save the current state to file.
    def writeToFile(self) -> None:
        with open(self.fileLocation, "wb") as file:
            pickle.dump(self.numberList, file)
            file.close()


class JSONFileRepository(FileRepositoryBase):
    # Constructor that reads from a file at the specified path.
    def __init__(self, filePath: str):
        self.fileLocation = filePath

        # File exists, load from it
        if os.path.exists(filePath):
            try:
                with open(filePath, "r") as file:
                    self.numberList = []
                    currentList = json.load(file) 
                    for number in currentList:
                        number = json.loads(number, cls = ComplexNumber)
                        self.numberList.append(number)
                    file.close()
            except:
                # Delete file as it is invalid and write the new numbers to the file.
                os.remove(filePath)
                self.writeToFile()

        # Use the already generated from memory and save the file.
        else:
            self.writeToFile()

    # Save the current state to file.
    def writeToFile(self) -> None:
        with open(self.fileLocation, "w") as file:
            json.dump(self.numberList, file)
            file.close()
