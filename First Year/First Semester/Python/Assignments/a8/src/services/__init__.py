#
#   Service for handling of the work is defined here.
#
import re
import random
import string
from repository import *

def generateRandomClient() -> Client:
    newClient = Client()
    newClient._id = random.randint(0, 100)
    newClient.Name = generateRandomString(30)
    return newClient

def generateRandomString(length : int):
    return ''.join(random.choice(string.ascii_letters) for x in range(length))

def generateRandomBook() -> Book:
    authors = ["abcdefgh", "aaaaaaaaa", "testauthor", "testauthor2"]
    newBook = Book()
    newBook._id = random.randint(0, 100)
    newBook._author = random.choice(authors)
    newBook._title = generateRandomString(10)
    return newBook

class BookRentalService:
    _storage : MemoryDataStorage = MemoryDataStorage()

    def __init__(self):                                         # pragma: no cover
        # Generate 20 books and add them to the repository.
        while len(self.getAllBooks()) != 20:
            try:
                self.addBook(generateRandomBook())
            except:
                pass
        
        # Generate 20 clients and add them to the repository.
        while len(self.getAllClients()) != 20:
            try:
                self.addClient(generateRandomClient())
            except:
                pass
    
        # Generate 5 past rentals and add them to the repository.
        while len(self.getAllRentedBooks()) != 5:
            try:
                self.addBookRental(
                    random.choice(self.getAllBooks()).ID,
                    random.choice(self.getAllClients()).ID
                )
            except:
                pass

    def addBook(self, book : Book) -> None:
        self._storage.addBook(book)

    def getAllBooks(self) -> list:
        return self._storage.books

    def getBookByID(self, bookID : int) -> Book:
        return self._storage.getBookByID(bookID)
        
    def updateBook(self, newState : Book) -> None:
        self._storage.updateBook(newState)

    def removeBook(self, bookID : int) -> None:
        self._storage.removeBook(bookID)

    def addClient(self, client : Client) -> None:
        self._storage.addClient(client)

    def getAllClients(self) -> list:
        return self._storage.clients

    def getClientByID(self, clientID : int) -> Client:
        return self._storage.getClientByID(clientID)
        
    def updateClient(self, newState : Client) -> None:
        self._storage.updateClient(newState)

    def removeClient(self, clientID : int) -> None:
        self._storage.removeClient(clientID)

    def getActiveRentals(self) -> list:
        allRentals = self._storage.getAllRentals()
        results = []
        for rental in allRentals:
            if rental.EndDate == None:
                results.append(rental)
        return results

    def getAllRentedBooks(self) -> list:
        results = []
        for book in self.getAllBooks():
            if self._storage.bookIsRented(book.ID):
                results.append(book)
        return results

    def getBookRentalCount(self, bookID : int) -> int:
        count = 0
        for rental in self._storage.getAllRentals():
            if rental.BookID == bookID:
                count += 1
        return count

    def getAuthorList(self) -> list:
        authors = []
        for book in self.getAllBooks():
            if not book.Author in authors:
                authors.append(book.Author)
        return authors

    def getClientRentalCount(self, client : Client) -> int:
        count = 0
        for rental in self._storage.getAllRentals():
            if rental.ClientID == client.ID:
                count += rental.Duration
        return count

    def getAuthorRentalCount(self, authorName : str) -> int:
        count = 0
        for rental in self._storage.getAllRentals():
            if self.getBookByID(rental.BookID).Author == authorName:
                count += 1
        return count

    def getAllUnrentedBooks(self) -> list:
        results = []
        for book in self.getAllBooks():
            if not self._storage.bookIsRented(book.ID):
                results.append(book)
        return results

    def addBookRental(self, bookID : int, clientID : int) -> None:
        self._storage.addBookRental(bookID, clientID)

    def endBookRental(self, bookID : int) -> None:
        self._storage.endBookRental(bookID)

    def search(self, stringToSearch : str):
        stringToSearch = stringToSearch.lower()
        clientResults = []
        for client in self.getAllClients():
            if re.findall(stringToSearch, str(client.ID).lower()) != [] or re.findall(stringToSearch, client.Name.lower()) != []:
                    clientResults.append(copy.deepcopy(client))
        bookResults = []
        for book in self.getAllBooks():
            if re.findall(stringToSearch, str(book.ID).lower()) != [] or re.findall(stringToSearch, book.Title.lower()) != [] or re.findall(stringToSearch, book.Author.lower()) != []:
                    bookResults.append(copy.deepcopy(book))
        return (clientResults, bookResults)
