import os
from services import *
from ui.errors import *

#
#   Auxiliary functions.
#
def readInteger(message : str) -> int:
    inputData = input(message)
    try:
        return int(inputData)
    except:
        raise IntegerReadException(inputData)

def clearScreen():
    if os.name == "nt":
        os.system("cls")
    else:
        os.system("clear")

def waitForEnter():
    input("Press enter to continue...")

def printErrorMessage(message : str) -> None:
    clearScreen()
    print(f"\nAn error has occured: { message }\n")
    waitForEnter()

def readClient() -> Client:
    client = Client()
    try:
        client._id = readInteger("Client ID: ")
    except:
        raise UIError("Client ID must be an integer!")
    client.Name = input("Client name: ")
    return client

def readBook() -> Book:
    book = Book()
    try:
        book._id = readInteger("Book ID: ")
    except:
        raise UIError("Book ID must be an integer!")
    book.Title = input("Book title: ")
    book.Author = input("Book author: ")
    return book

def printSplashText(message : str) -> None:
    clearScreen()
    print(f"\n{ message }\n")
    waitForEnter()

#
#   UI wrapper is defined here.
#
class UI:
    running : bool = False
    service : BookRentalService

    def __init__(self):
        self.running = True
        self.service = BookRentalService()

    def _printMenu(self):
        clearScreen()
        print("\nWelcome to the Book Rental Simulator!\n")
        print("1. Manage clients and books.")
        print("2. Manage rentals.")
        print("3. Search the database.")
        print("4. Create statistics.")
        print("5. Exit the app.\n")

    def _listAllBooks(self):
        allBooks = self.service.getAllBooks()
        if len(allBooks) == 0:
            printSplashText("There are no books.")
        else:
            resultText = ""
            for book in allBooks:
                resultText += f"- { book }\n"
            printSplashText(resultText)

    def _addBook(self):
        try:
            clearScreen()
            self.service.addBook(readBook())
            printSplashText("Book added successfully!")
        except StorageError as error:
            printErrorMessage(error)

    def _updateBook(self):
        clearScreen()
        book = Book()
        try:
            book._id = readInteger("Book ID: ")
            book = self.service.getBookByID(book._id)
            if book == None:
                raise UIError("Book with specified ID does not exist.")
            print(f"Currently editing | { book }.")
            book.Title = input("New book title (leave empty for no change): ")
            book.Author = input("New book author (leave empty for no change): ")
            self.service.updateBook(book)
            printSplashText("Book has been edited successfully.")
        except UIError as error:
            printErrorMessage(error)

    def _removeBook(self):
        clearScreen()
        try:
            bookID = readInteger("Book ID: ")
        except MenuInputError as error:
            printErrorMessage(error)
        try:
            self.service.removeBook(bookID)
            printSplashText("Book has been removed successfully!")
        except StorageError as error:
            printErrorMessage(error)
        
    def _listAllClients(self):
        allClients = self.service.getAllClients()
        if len(allClients) == 0:
            printSplashText("There are no clients.")
        else:
            resultText = ""
            for client in allClients:
                resultText += f"- { client }\n"
            printSplashText(resultText)

    def _addClient(self):
        try:
            clearScreen()
            self.service.addClient(readClient())
            printSplashText("Client added successfully!")
        except StorageError as error:
            printErrorMessage(error)

    def _updateClient(self):
        clearScreen()
        client = Client()
        try:
            client._id = readInteger("Client ID: ")
            client = self.service.getClientByID(client._id)
            if client == None:
                raise UIError("Client with specified ID does not exist.")
            print(f"Currently editing | { client }.")
            client.Name = input("New client name (leave empty for no change): ")
            self.service.updateClient(client)
            printSplashText("Client has been edited successfully.")
        except UIError as error:
            printErrorMessage(error)

    def _removeClient(self):
        clearScreen()
        try:
            clientID = readInteger("Client ID: ")
        except MenuInputError as error:
            printErrorMessage(error)
        try:
            self.service.removeClient(clientID)
            printSplashText("Client has been removed successfully!")
        except StorageError as error:
            printErrorMessage(error)

    def _managingMenu(self):
        running = True
        while running:
            clearScreen()
            print("-------Books-------")
            print("1. Add a new book.")
            print("2. Remove a book.")
            print("3. Update a book.")
            print("4. List all books.")
            print("")
            print("------Clients------")
            print("5. Add a new client.")
            print("6. Remove a client.")
            print("7. Update a client.")
            print("8. List all clients.")

            print("\n9. Go back.\n")

            chosenResult = readInteger("Action > ")
            match chosenResult:
                case 1:
                    self._addBook()
                case 2:
                    self._removeBook()
                case 3:
                    self._updateBook()
                case 4:
                    self._listAllBooks()
                case 5:
                    self._addClient()
                case 6:
                    self._removeClient()
                case 7:
                    self._updateClient()
                case 8:
                    self._listAllClients()
                case 9:
                    running = False
                case other:
                    raise MenuInputError(chosenResult)

    def _rentBook(self):
        clearScreen()
        print("Unrented books:")
        print("---------------")
        for book in self.service.getAllUnrentedBooks():
            print(f"{ book }")
        try:
            idToRent = readInteger("\nEnter ID of the book to be rented: ")
            clientID = readInteger("Enter ID of the client that wants to rent the book: ")
            self.service.addBookRental(idToRent, clientID)
            printSplashText("Rental has been added successfully!")
        except StorageError as error:
            printErrorMessage(error)

    def _unrentBook(self):
        clearScreen()
        print("Currently rented books:")
        print("-----------------------")
        for book in self.service.getAllRentedBooks():
            print(f"{ book }")
        try:
            idToUnrent = readInteger("\nEnter ID of the book to be returned: ")
            self.service.endBookRental(idToUnrent)
            printSplashText("Rental has been ended successfully!")
        except StorageError as error:
            printErrorMessage(error)

    def _statisticsMenu(self):
        running = True
        while running:
            clearScreen()
            print("\n----Statistics----")
            print("1. Most rented books.")
            print("2. Most active clients.")
            print("3. Most rented authors.")
            print("\n4. Go back.\n")

            chosenResult = readInteger("Action > ")
            match chosenResult:
                case 1:
                    clearScreen()
                    print("Books sorted by rentals:")
                    print("--------------------------")
                    books = self.service.getAllBooks()
                    bookDataList = []
                    RENTAL_COUNT = 0
                    BOOK = 1
                    rentals = self.service.getActiveRentals()
                    for book in books:
                        bookDataList.append([self.service.getBookRentalCount(book.ID), book])
                    bookDataList.sort(key = lambda bookData: -bookData[RENTAL_COUNT])
                    for bookData in bookDataList:
                        print(f"{ bookData[BOOK] } - { bookData[RENTAL_COUNT] } rentals")
                    print("")
                    waitForEnter()
                case 2:
                    clearScreen()
                    print("Clients sorted by activity:")
                    print("--------------------------")
                    clients = self.service.getAllClients()
                    clientDataList = []
                    for client in clients:
                        clientDataList.append([self.service.getClientRentalCount(client), client])
                    RENTAL_COUNT = 0
                    CLIENT = 1
                    clientDataList.sort(key = lambda clientData: -clientData[RENTAL_COUNT])
                    for clientData in clientDataList:
                        print(f"{ clientData[CLIENT] } - { clientData[RENTAL_COUNT] } rented days")
                    print("")
                    waitForEnter()
                case 3:
                    clearScreen()
                    print("Authors sorted by rentals:")
                    print("--------------------------")
                    authors = self.service.getAuthorList()
                    authorDataList = []
                    for author in authors:
                        authorDataList.append([self.service.getAuthorRentalCount(author), author])
                    RENTAL_COUNT = 0
                    AUTHOR = 1
                    authorDataList.sort(key = lambda authorData: -authorData[RENTAL_COUNT])
                    for authorData in authorDataList:
                        print(f"{ authorData[AUTHOR] } - { authorData[RENTAL_COUNT] } rentals")
                    print("")
                    waitForEnter()
                case 4:
                    running = False
                case other:
                    raise MenuInputError(chosenResult)

    def _rentalManagementMenu(self):
        running = True
        while running:
            clearScreen()
            print("\n-----Rentals-----")
            print("1. Rent a book.")
            print("2. Return a book.")
            print("\n3. Go back.\n")

            chosenResult = readInteger("Action > ")
            match chosenResult:
                case 1:
                    self._rentBook()
                case 2:
                    self._unrentBook()
                case 3:
                    running = False
                case other:
                    raise MenuInputError(chosenResult)

    def _searchMenu(self):
        clearScreen()
        inputData = input("\nWhat are we looking for?\nInput: ")
        (clientList, bookList) = self.service.search(inputData)
        if len(clientList) != 0:
            print("\nClients: ")
            for client in clientList:
                print(f"{ client }")
            print("")
        if len(bookList) != 0:
            print("\nBooks:")
            for book in bookList:
                print(f"{ book }")
            print("")
        waitForEnter()

    def start(self):
        # App main loop
        while self.running:
            self._printMenu()

            # Read menu option
            chosenResult = 0
            try:
                chosenResult = readInteger("Action > ")
                match chosenResult:
                    case 1:
                        self._managingMenu()
                    case 2:
                        self._rentalManagementMenu()
                    case 3:
                        self._searchMenu()
                    case 4:
                        self._statisticsMenu()
                    case 5:
                        self.running = False
                    case other:
                        raise MenuInputError(chosenResult)
            except UIError as error:
                printErrorMessage(error)
        
        # End credits.
        printSplashText("Bye!")
