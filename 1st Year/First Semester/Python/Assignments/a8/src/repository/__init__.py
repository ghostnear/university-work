#
#   Repository for data storage is defined here.
#
import copy
import datetime
from domain import *
from repository.errors import *

SEARCH_POSITION_NONEXISTENT = -1

class BaseDataStorage:
    pass

class MemoryDataStorage(BaseDataStorage):
    _books = []
    _clients = []
    _rentals = []

    @property
    def books(self):
        return self._books[:]

    def _getBookPosition(self, bookID : int) -> int:
        index = 0
        for book in self._books:
            if book.ID == bookID:
                return index
            index += 1
        return SEARCH_POSITION_NONEXISTENT

    def getBookByID(self, bookID : int) -> Book:
        for book in self._books:
            if bookID == book.ID:
                return copy.deepcopy(book)
        return None

    def hasBook(self, bookID : int) -> bool:
        return self._getBookPosition(bookID) != SEARCH_POSITION_NONEXISTENT

    def addBook(self, newBook : Book) -> None:
        if self.hasBook(newBook.ID):
            raise BookDuplicateError(self._books[self._getBookPosition(newBook.ID)])
        self._books.append(copy.deepcopy(newBook))

    def updateBook(self, newState : Book) -> None:
        if not self.hasBook(newState.ID):
            raise IDNotFoundError(newState.ID)
        pos = self._getBookPosition(newState.ID)
        if newState.Title != "":
            self._books[pos].Title = newState.Title
        if newState.Author != "":
            self._books[pos].Author = newState.Author  
    
    def removeBook(self, bookID : int) -> None:
        bookPosition = self._getBookPosition(bookID)
        if bookPosition == SEARCH_POSITION_NONEXISTENT:
            raise IDNotFoundError(bookID)
        self._books.pop(bookPosition)

    @property
    def clients(self):
        return self._clients[:]

    def _getClientPosition(self, clientID : int) -> int:
        index = 0
        for client in self._clients:
            if client.ID == clientID:
                return index
            index += 1
        return SEARCH_POSITION_NONEXISTENT

    def getClientByID(self, clientID : int) -> Book:
        for client in self._clients:
            if clientID == client.ID:
                return copy.deepcopy(client)
        return None

    def addClient(self, newClient : Client) -> None:
        pos = self._getClientPosition(newClient.ID)
        if pos != SEARCH_POSITION_NONEXISTENT:
            raise ClientDuplicateError(self._clients[pos])
        self._clients.append(copy.deepcopy(newClient))

    def updateClient(self, newState : Client) -> None:
        pos = self._getClientPosition(newState.ID)
        if pos == SEARCH_POSITION_NONEXISTENT:
            raise IDNotFoundError(newState.ID)
        self._clients[pos].Name = newState.Name
    
    def removeClient(self, clientID : int) -> None:
        clientPosition = self._getClientPosition(clientID)
        if clientPosition == SEARCH_POSITION_NONEXISTENT:
            raise IDNotFoundError(clientID)
        self._clients.pop(clientPosition)

    def bookIsRented(self, bookID : int):
        for rental in self.getAllRentals():
            if rental.BookID == bookID and rental.EndDate == None:
                return True
        return False

    def getAllRentals(self) -> list:
        return self._rentals[:]

    def addBookRental(self, bookID : int, clientID : int) -> None:
        newRental = Rental()
        if len(self._rentals) > 0:
            newRental._id = self._rentals[-1]._id + 1
        else:
            newRental._id = 0
        newRental._bookID = bookID
        newRental.ClientID = clientID
        newRental._startDate = datetime.datetime.now()
        newRental._endDate = None
        if not self.hasBook(bookID):
            raise StorageError("Book does not exist!")
        if self.getClientByID(clientID) == None:
            raise StorageError("Client does not exist!")
        if self.bookIsRented(bookID):
            raise StorageError("Book is already rented!")
        for rental in self.getAllRentals():
            if newRental.ID == rental.ID:
                raise StorageError("Rental ID already used!")
        self._rentals.append(newRental)

    def endBookRental(self, bookID : int) -> None:
        for rental in self.getAllRentals():
            if rental.BookID == bookID and rental.EndDate == None:
                rental._endDate = datetime.datetime.now()
                return
        raise StorageError("Book is not currently rented!")