#
#   Repository errors are defined here.
#
from domain import *

class StorageError(Exception):
    _message : str = "A generic storage error has occured!"

    def __init__(self, message : str):      # pragma: no cover
        self._message = message

    def __str__(self):                      # pragma: no cover
        return self._message

class IDNotFoundError(StorageError):
    _invalidID : int = 0

    def __init__(self, id : int):           # pragma: no cover
        self._invalidID = id

    def __str__(self) -> str:               # pragma: no cover
        return f"Entity with ID { self._invalidID } could not be found!"

class BookDuplicateError(StorageError):
    _validBook : Book

    def __init__(self, book : Book):        # pragma: no cover
        self._validBook = book

    def __str__(self) -> str:               # pragma: no cover
        return f"Book with ID { self._validBook.ID } already exists as { self._validBook.canonicalName() }!"

class ClientDuplicateError(StorageError):
    _validClient : Client

    def __init__(self, client : Client):    # pragma: no cover
        self._validClient = client

    def __str__(self) -> str:               # pragma: no cover
        return f"Book with ID { self._validClient.ID } already exists as { self._validClient.Name }!"