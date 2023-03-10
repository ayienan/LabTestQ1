#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}
int main() {
    int sockfd; 
    struct sockaddr_in server_addr; 
    char buffer[256]; 
    int n; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error is opening socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.56.1");
    server_addr.sin_port = htons(8080);

    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        error("Connecting is error");

    bzero(buffer, sizeof(buffer));

    n = read(sockfd, buffer, sizeof(buffer)-1);
    if (n < 0) 
        error("Error reading from socket");

    printf("Random number: %s\n", buffer);

    close(sockfd);
    return 0;
}
