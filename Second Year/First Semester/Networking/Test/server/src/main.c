#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

char* map;
int mapSize;

bool is_game_ended(char* map)
{
    for(int index = 0; index < mapSize; index++)
        if(map[index] == 'u')
            return false;

    return true;
}

void broadcast_status()
{
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket < 0)
    {
        fprintf(stderr, "Couldn't create UDP socket!\n");
        return;
    }

    int broadcast = '1';
    if(setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
    {
        printf("Error while setting UDP broadcasting option!\n");
        return;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;

    struct hostent *hp = gethostbyname("127.0.0.1");
    if(hp==0)
    {
        fprintf(stderr, "Unknown host!\n");
        return;
    }

    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);

    server.sin_port = htons(12565);

    int totalBytes = sendto(udp_socket, map, mapSize + 1, 0, &server, sizeof(struct sockaddr_in));
    if(totalBytes < 0)
    {
        fprintf(stderr, "Couldn't broadcast data!\n");
        return; 
    }
}

void handle_client(void* clientPointer)
{
    int clientSocket = *((int*)clientPointer);

    uint16_t index;
    char value;

    while(!is_game_ended(map))
    {
        int totalbytes = recv(clientSocket, &index, 2, MSG_WAITALL);
        totalbytes += recv(clientSocket, &value, 1, MSG_WAITALL);

        // Something happened, abort.
        if(totalbytes != 3)
        {
            fprintf(stderr, "A client closed its connection!\n");
            return;
        }


        if(map[index] == 'u')
            map[index] = value;

        fprintf(stderr, "Host game status: %s\n", map);

        broadcast_status();
    }

    close(clientSocket);
    free((int*)clientPointer);
}

int main()
{
    mapSize = 10;
    map = malloc(sizeof(char) * (mapSize + 1));
    memset(map, 0, sizeof(char) * (mapSize + 1));
    memset(map, 'u', sizeof(char) * mapSize);

    // Connection recieve socket.
    int tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0)
    {
        printf("Error occured on socket creation!\n");
        return -1;
    }

    struct sockaddr_in tcp_server;
    memset(&tcp_server, 0, sizeof(struct sockaddr_in));
    tcp_server.sin_family = AF_INET;
    tcp_server.sin_port = htons(25565);
    tcp_server.sin_addr.s_addr = INADDR_ANY;

    int result_sock = bind(tcp_sock, (struct sockaddr *) &tcp_server, sizeof(struct sockaddr_in));
    if(result_sock < 0)
    {
        printf("Socket is already used!");
        return -1;
    }

    listen(tcp_sock, 5);

    while(!is_game_ended(map))
    {
        // Listen for clients
        struct sockaddr_in tcp_client;
        memset(&tcp_client, 0, sizeof(tcp_client));
        int length = sizeof(tcp_client);

        printf("Waiting for clients...\n");

        int* current_client_socket = malloc(sizeof(int));
        *current_client_socket = accept(tcp_sock, (struct sockaddr *) &tcp_client, &length);
        printf("Client with address %s and port %d connected.\n", inet_ntoa(tcp_client.sin_addr), ntohs(tcp_client.sin_port));

        pthread_t newThread;
        if(pthread_create(&newThread, NULL, &handle_client, current_client_socket))
        {
            printf("An error occured while creating a thread for handling the client!\n");
            exit(-1);
        }
        pthread_detach(newThread);
    }

    close(tcp_sock);

    return 0;
}

