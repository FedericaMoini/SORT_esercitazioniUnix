#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUF_SIZE 1024

int main(int argc, char *argv[]){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE];

    if (sockfd < 0) {
        perror("Errore nella creazione della socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Errore nella connessione al server");
        close(sockfd);
        exit(1);
    }

    send(sockfd, "LIST", 5, 0);
    recv(sockfd, buffer, BUF_SIZE, 0);
    printf("Lista titoli disponibili:\n%s\n", buffer);

    char agentName[50];
    printf("Inserisci il nome dell'agente da cui acquistare un'azione: ");
    scanf("%s", agentName);

    char request[BUF_SIZE];
    sprintf(request, "BUY|%s", agentName);
    send(sockfd, request, strlen(request) + 1, 0);

    close(sockfd);
    return 0;
}