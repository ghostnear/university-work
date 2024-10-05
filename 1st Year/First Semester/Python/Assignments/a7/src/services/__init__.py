#
#   Services for operations with complex numbers.
#

import os
from domain import *


class Service:
    repository: RepositoryBase = RepositoryBase()

    def __init__(self):
        # Check for settings existence and set up the service accordingly.
        if os.path.exists("settings.properties"):
            with open("settings.properties", "r") as file:
                readFile = json.load(file)
                if "repository" in readFile:
                    fileName = ""
                    if "fileName" in readFile:
                        fileName = readFile["fileName"]

                    match readFile["repository"]:
                        case "json":
                            self.repository = JSONFileRepository(fileName)
                        case "binary":
                            self.repository = BinaryFileRepository(fileName)
                        case "text":
                            self.repository = TextFileRepository(fileName)
                        case "memory":
                            self.repository = MemoryRepository()
                        case other:     #
                            pass        # Do nothing and just use memory repo.
                file.close()
        else:
            with open("settings.properties", "w") as file:
                json.dump({"fileName": "", "repository": "memory"}, file)

    def undo(self) -> None:
        self.repository.undo()

    def filterInterval(self, left: int, right: int) -> None:
        currentList = self.getAllNumbers()
        left -= 1
        right -= 1

        # Invalid indexes
        if(left < 0 or left > len(currentList) or right < left or right < 0 or right > len(currentList)):
            raise IndexError("Invalid index bounds!")

        currentList = currentList[left : right + 1]
        self.repository.updateHistory()
        self.repository.saveFromList(currentList)

    def saveComplexNumber(self, real: float, imaginary: float) -> None:
        value = ComplexNumber(real, imaginary)
        self.repository.updateHistory()
        self.repository.saveComplexNumber(value)

    def getAllNumbers(self) -> list:
        return self.repository.getAsList()
