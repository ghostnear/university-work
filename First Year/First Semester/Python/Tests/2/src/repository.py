#
#   Repository here.
#
from src.domain import *

class RepositoryException(Exception):
    pass

class AssignmentFileRepository:
    _path : str
    _assignmentList : list = []

    def addAssignment(self, newAssignment : Assignment):
        # Check if ID is already there.
        for assignment in self._assignmentList:
            if assignment.ID == newAssignment.ID:
                raise RepositoryException("Assignment already exists in the repository!")
        self._assignmentList.append(newAssignment)
    
    def __init__(self, path : str):
        try:
            with open(path, "r") as file:
                inputLines = file.readlines()
                for line in inputLines:
                    splitLine = line.split(",")
                    for index in range(3):
                        splitLine[index] = splitLine[index].strip()
                    newAssignment = Assignment(int(splitLine[0]), splitLine[1], splitLine[2])
                    self.addAssignment(newAssignment)
                self._path = path
                file.close()
        except RepositoryException as error:    #
            raise error                         # Propagate error.
        except FileNotFoundError:
            raise RepositoryException(f"Repository input file { path } could not be found!")

    def save(self):
        with open(self._path, "w") as file:
            for assignment in self.AssignmentList:
                file.write(f"{ assignment._toFileFormatString() }\n")
            file.close()

    @property
    def AssignmentList(self):
        return self._assignmentList[:]