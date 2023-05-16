#
#   Service here.
#
from src.repository import *

class ServiceError(Exception):
    pass

class AssignmentService:
    _repository : AssignmentFileRepository

    def __init__(self):
        try:
            self._repository = AssignmentFileRepository("assignments.txt")
        except RepositoryException as error:
            raise ServiceError(f"An error occured while creating the repository: \n\n{ str(error) }\n")

    def addAssigment(self, newID : int, newName : str, newSolution : str):
        try:
            newAssignment = Assignment(newID, newName, newSolution)
            self._repository.addAssignment(newAssignment)
            self._repository.save()
        except AssignmentError as error:
            raise ServiceError(str(error))
        except RepositoryException as error:
            raise ServiceError(str(error))

    def getSolutionWords(self, solution : str):
        resultWords = {}
        splitWords = solution.split(" ")
        for word in splitWords:
            # Valid word
            if word.isalnum():
                if word in resultWords:
                    resultWords[word] += 1
                else:
                    resultWords[word] = 1
        return resultWords

    def checkSimilarity(self, firstAssignment : Assignment, secondAssignment : Assignment) -> float:
        firstSolutionWords = self.getSolutionWords(firstAssignment.Solution)
        secondSolutionWords = self.getSolutionWords(secondAssignment.Solution)
        firstCommonWords = 0
        for word in firstSolutionWords:
            if word in secondSolutionWords:
                firstCommonWords += secondSolutionWords[word]
        secondCommonWords = 0
        for word in secondSolutionWords:
            if word in firstSolutionWords:
                secondCommonWords += firstSolutionWords[word]
        return max(firstCommonWords / len(secondSolutionWords), secondCommonWords / len(firstSolutionWords))


    def reportHonesty(self) -> list:
        result = []
        assignments = self._repository.AssignmentList
        for firstIndex in range(len(assignments)):
            for secondIndex in range(firstIndex, len(assignments)):
                # Only different students
                if firstIndex != secondIndex:
                    firstAssignment = self._repository.AssignmentList[firstIndex]
                    secondAssignment = self._repository.AssignmentList[secondIndex]
                    checkResult = int(self.checkSimilarity(firstAssignment, secondAssignment) * 100)
                    if checkResult >= 20:
                        result.append(f"{ firstAssignment.Name } { secondAssignment.Name } : ({ checkResult }% of the solution is common)")
        return result

    def getAssignments(self) -> list:
        return self._repository.AssignmentList