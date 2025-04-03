#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define BUF_SIZE 1000
#define PORT 8000

int main(){
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Error opening socket");
        exit(1);
    }

    struct hostent* server = gethostbyname("localhost");
    if(server == NULL){
        perror("No such host");
        exit(1);
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        perror("Error connecting to server");
        exit(1);
    }

    printf("Enter actuator name: ");
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    if(send(sockfd, buffer, strlen(buffer), 0) == -1){
        perror("Error on send");
        exit(1);
    }

    printf("Actuator '%s' registered.\n", buffer);
    close(sockfd);

    return 0;
}