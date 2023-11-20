#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>

bool ended = false;
int tcp_sock;

void send_data(int signal)
{
    uint16_t random_value = rand() % 10;
    int totalBytes = send(tcp_sock, &random_value, 2, 0);

    char random_char = 'a' + rand() % 10;
    totalBytes = send(tcp_sock, &random_char, 1, 0);

    alarm(1);
}

int main()
{
    srand(time(NULL));

    // Server connection socket.
    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0)
    {
        printf("Error creating client socket!\n");
        return -1;
    }

    struct sockaddr_in tcp_server;
    memset(&tcp_server, 0, sizeof(tcp_server));
    tcp_server.sin_family = AF_INET;
    tcp_server.sin_port = htons(25565);
    tcp_server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int result_sock = connect(tcp_sock, (struct sockaddr *) &tcp_server, sizeof(struct sockaddr_in));
    if(result_sock < 0)
    {
        printf("Error connecting to the server!\n");
        return -1;
    }

    signal(SIGALRM, send_data);
    alarm(1);

    // UDP socket for listening.
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket < 0)
    {
        printf("Error while creating UDP socket for listening!\n");
        return -1;
    }

    /*  Doesn't work for some reason... idk?
        Otherwise we would've got more clients...
    char broadcast = '1';
    if(setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
    {
        printf("Error while setting UDP broadcasting option!\n");
        return -1;
    }*/

    struct sockaddr_in udp_server;
    bzero(&udp_server, sizeof(udp_server));
    udp_server.sin_family=AF_INET;
    udp_server.sin_addr.s_addr=INADDR_ANY;
    udp_server.sin_port=htons(12565);

    if(bind(udp_socket,(struct sockaddr *)&udp_server, sizeof(udp_server)) < 0)
    {
        printf("Error while binding UDP socket for listening!\n");
        return -1;
    }

    char mapData[15] = {0};

    while(!ended)
    {
        struct sockaddr_in client;
        int clientLength = sizeof(client);
        int totalBytes = recvfrom(udp_socket, mapData, 15, 0, (struct sockaddr *)&client, &clientLength);
        if(totalBytes < 0)
        {
            fprintf(stderr, "Error while recieving UDP data!\n");
            exit(-1);
        }

        fprintf(stderr, "Client game status: %s\n", mapData);
    }

    close(tcp_sock);

    return 0;
}