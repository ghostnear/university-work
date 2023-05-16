#
#   PyUnit tests are defined here.
#
from services import *

def init_tests():
    service = BookRentalService()
    service._storage._rentals =[]   #
    service._storage._books = []    #
    service._storage._clients = []  # Clear everything forcefully.

    return service

def test_all():
    service = init_tests()

    # Add valid client
    newClient = Client()
    newClient._id = 10
    newClient.Name = "Also Me"
    service.addClient(newClient)
    results = service.getAllClients()
    assert len(results) == 1 and results[0].ID == newClient.ID and results[0].Name == newClient.Name, "Client adding failed."
    assert service.getClientByID(10) != None, "Client ID getting not working."

    # Add duplicate client
    try:
        service.addClient(newClient)
        assert False, "Duplicate client added."                           # pragma: no cover
    except:
        pass

    # Remove nothing
    try:
        service.removeClient(11)
        assert False, "Non-existent client should not be deleted."        # pragma: no cover
    except:
        pass

    # Remove valid client
    service.removeClient(10)
    results = service.getAllClients()
    assert service.getClientByID(10) == None, "Removing did not work."    # pragma: no cover

    # Add original client again
    service.addClient(newClient)

    # Update unknown client
    newClient._id = 0
    try:
        service.updateClient(newClient)
        assert False, "Tried to edit non existent client."                # pragma: no cover
    except:
        pass

    # Update the client's info
    newClient._id = 10
    newClient.Name = "Not Me"
    service.updateClient(newClient)
    results = service.getAllClients()
    assert len(results) == 1 and results[0].ID == newClient.ID and results[0].Name == newClient.Name, "Updating client did not work."

    # Test searching
    (bookResults, clientResults) = service.search("e")
    assert len(bookResults) == 1 and len(clientResults) == 0, "Search found too much."

    # Add valid book
    newBook = Book()
    newBook._id = 10
    newBook.Title = "Test"
    newBook.Author = "Me"
    service.addBook(newBook)
    results = service.getAllBooks()
    assert len(results) == 1 and results[0].ID == newBook.ID and results[0].Author == newBook.Author and results[0].Title == newBook.Title, "Book adding failed."
    assert service.getBookByID(10) != None, "Book ID getting not working."

    # Add duplicate book
    try:
        service.addBook(newBook)
        assert False, "Duplicate book added."                           # pragma: no cover
    except:
        pass

    # Remove nothing
    try:
        service.removeBook(11)
        assert False, "Non-existent book should not be deleted."        # pragma: no cover
    except:
        pass

    # Remove valid book
    service.removeBook(10)
    results = service.getAllBooks()
    assert service.getBookByID(10) == None, "Removing did not work."    # pragma: no cover

    # Add original book again
    service.addBook(newBook)

    # Update unknown book
    newBook._id = 0
    try:
        service.updateBook(newBook)
        assert False, "Tried to edit non existent book."                # pragma: no cover
    except:
        pass

    # Update the book's info
    newBook._id = 10
    newBook.Title = "b"
    newBook.Author = "e"
    service.updateBook(newBook)
    results = service.getAllBooks()
    assert len(results) == 1 and results[0].ID == newBook.ID and results[0].Author == newBook.Author and results[0].Title == newBook.Title, "Updating book did not work."

    # Test searching
    (bookResults, clientResults) = service.search("e")
    assert len(bookResults) == 1 and len(clientResults) == 1, "Search found too much."

    # Add rental
    service.addBookRental(10, 10)
    assert len(service.getAuthorList()) == 1, "Author list does not generate properly."
    assert service.getBookRentalCount(10) == 1, "Rental counting wrong"
    assert len(service.getActiveRentals()) == 1 and len(service.getAllRentedBooks()) == 1 and len(service.getAllUnrentedBooks()) == 0, "Rental counting wrong."
    assert service.getAuthorRentalCount("e") == 1 and service.getClientRentalCount(service.getClientByID(10)) == 1, "Statistics counting wrong."
    service.endBookRental(10)
    assert len(service.getActiveRentals()) == 0 and len(service.getAllRentedBooks()) == 0 and len(service.getAllUnrentedBooks()) == 1, "Rental counting wrong."

if __name__ == "__main__":
    test_all()