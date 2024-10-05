from domain.client import Client
from repository.repository_exception import RepositoryException


class ClientRepo:
    # TODO Finish implementation
    def __init__(self):
        self._clients = {}

    def add(self, client):
        if client.id in self._clients.keys():
            raise RepositoryException("Duplicate Client id")
        self._clients[client.id] = client
