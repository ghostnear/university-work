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
    int tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
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

    close(tcp_sock);

    return 0;
}