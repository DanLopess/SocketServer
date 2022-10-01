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
    // create server info structure
    struct sockaddr_in server = {0};
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = inet_addr("localhost");

    socklen_t server_info_len = sizeof(server);

    // create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sfd)
    {
        perror("socket");
        return -1;
    }

    // connect to server

    if (0 > connect(sfd, (struct sockaddr *)&server, server_info_len))
    {
        perror("connect");
        return -1;
    }

    // receive data

    char buffer[1024];
    ssize_t bytes_read = recv(sfd, buffer, sizeof(buffer), 0);
    if (0 > bytes_read)
    {
        perror("recv");
        return -1;
    }

    printf("Received %ld bytes: %s", bytes_read, buffer);

    // clean up

    close(sfd);

    return 0;
}
