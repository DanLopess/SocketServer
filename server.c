#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // create socket info structure
    struct sockaddr_in server = {0};
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);

    socklen_t server_info_len = sizeof(server);

    struct sockaddr_in client = {0};
    socklen_t client_info_len = sizeof(client);

    // create our socket (server file descriptor)
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sfd)
    {
        perror("socket");
        return -1;
    }

    // bind socket to port

    if (0 > bind(sfd, (struct sockaddr *)&server, server_info_len))
    {
        perror("bind");
        return -1;
    }

    // listen for connections

    if (0 > listen(sfd, 0))
    {
        perror("listen");
        return -1;
    }

    // accept connection (client file descriptor)
    printf("Waiting for connection...\n");
    int cfd = accept(sfd, (struct sockaddr *)&client, &client_info_len);
    if (0 > cfd)
    {
        perror("accept");
        return -1;
    }

    // send data to client

    char *msg = "Hello from server";
    if (0 > send(cfd, msg, strlen(msg), 0))
    {
        perror("send");
        return -1;
    }

    // close connection

    close(cfd);
    close(sfd);

    return 0;
}
