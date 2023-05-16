#
#   Domain entities here.
#
class AssignmentError(Exception):
    pass

class Assignment:
    _id : int
    _name : str
    _solution : str

    def __init__(self, newID : int, name : str, solution : str):
        self._id = newID
        
        if len(name) < 3:
            raise AssignmentError("Student name must be 3 characters long!")
        self._name = name

        if solution == "":
            raise AssignmentError("The solution of the assignment can't be empty!")
        self._solution = solution

    def __str__(self) -> str:
        return f"ID: { self._id }\nName: { self._name }\nSolution: { self._solution }"

    def _toFileFormatString(self) -> str:
        return f"{ self._id }, { self._name }, { self._solution }"

    @property
    def ID(self) -> int:
        return self._id

    @property
    def Name(self) -> str:
        return self._name

    @property
    def Solution(self) -> str:
        return self._solution