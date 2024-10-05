#
#   UI errors are defined here.
#
class UIError(Exception):
    _message : str = "A generic UI error has occured!"

    def __init__(self, message : str):
        self._message = message

    def __str__(self):
        return self._message

class IntegerReadException(UIError):
    _invalidData : str = ""

    def __init__(self, data : str):
        self._invalidData = data

    def __str__(self) -> str:
        return f"'{ self._invalidData }' could not be parsed as an integer."

class MenuInputError(UIError):
    _invalidInput : int = 0

    def __init__(self, input : int):
        self._invalidInput = input

    def __str__(self) -> str:
        return f"'{ self._invalidInput }' is not a valid menu option."
