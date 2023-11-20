#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
int main()
{
    // Connecction recieve socket.
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

    while(true)
    {
        // Listen for clients
        struct sockaddr_in tcp_client;
        memset(&tcp_client, 0, sizeof(tcp_client));
        int length = sizeof(tcp_client);

        printf("Waiting for clients...\n");

        int current_client = accept(tcp_sock, (struct sockaddr *) &tcp_client, &length);
        printf("Client with address %s and port %d connected.\n", inet_ntoa(tcp_client.sin_addr), ntohs(tcp_client.sin_port));
    
        // TODO: spawn a thread to treat the client here.
        // send the current_client as an argument to the thread.
    }

    close(tcp_sock);

    return 0;
}