#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, new_sock; 
    struct sockaddr_in server_addr, client_addr; 
    char buffer[256]; 
    int random_num; 
    int n; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error to open socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
        error("Find error in binding");

    listen(sockfd, 5);
    socklen_t client_length = sizeof(client_addr);
    new_sock = accept(sockfd, (struct sockaddr *) &client_addr, &client_length);
    if (new_sock < 0) 
        error("Error on accept");

    srand(time(NULL));
    random_num = (rand() % 900) + 100;

    sprintf(buffer, "%d", random_num);

    n = write(new_sock, buffer, sizeof(buffer));
    if (n < 0) error("Error writing to socket");

    close(new_sock);
    close(sockfd);
    return 0;
}
