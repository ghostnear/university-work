#
#   Domain entities are defined here.
#
import datetime

class Book:
    _id : int
    _title : str
    _author : str

    @property
    def ID(self) -> int:
        return self._id

    @property
    def Title(self) -> str:
        return self._title

    @Title.setter
    def Title(self, newTitle : str) -> None:
        self._title = newTitle

    @property
    def Author(self) -> str:
        return self._author

    @Author.setter
    def Author(self, newAuthor : str) -> None:
        self._author = newAuthor

    def canonicalName(self) -> str:                             # pragma: no cover
        return self.Title + " by " + self.Author

    def __str__(self) -> str:                                   # pragma: no cover
        return self.canonicalName() + " | ID: " + str(self.ID)

class Client:
    _id : int
    _name : str

    @property
    def ID(self) -> int:
        return self._id

    @property
    def Name(self) -> str:
        return self._name

    @Name.setter
    def Name(self, newName : str) -> None:
        self._name = newName

    def __str__(self) -> str:                                   # pragma: no cover
        return self.Name + " | ID: " + str(self.ID)

class Rental:
    _id : int
    _bookID : int
    _clientID : int
    _startDate : datetime.datetime
    _endDate : datetime.datetime

    @property
    def ID(self) -> int:
        return self._id

    @property
    def BookID(self) -> int:
        return self._bookID

    @BookID.setter
    def BookID(self, newID : int):
        self._bookID = newID

    @property
    def ClientID(self) -> int:
        return self._clientID

    @ClientID.setter
    def ClientID(self, newID : int):
        self._clientID = newID

    @property
    def StartDate(self) -> datetime.datetime:
        return self._startDate

    @property
    def EndDate(self) -> datetime.datetime:
        return self._endDate

    @property
    def Duration(self) -> int:
        if self._endDate == None:
            return (datetime.datetime.now() - self._startDate).days + 1
        return (self._endDate - self._startDate).days + 1