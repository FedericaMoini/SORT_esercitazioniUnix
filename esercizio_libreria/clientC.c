#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 8000

int main(int argc, char *argv[]){
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    char msg[100];
    sprintf(msg, "C|%s|%s", argv[1], argv[2]);
    send(sockfd, msg, strlen(msg)+1, 0);
    
    close(sockfd);
    return 0;
}