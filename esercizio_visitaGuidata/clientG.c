#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUF_SIZE 100

int main(){
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Errore apertura socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Errore connessione");
        exit(1);
    }

    char name[30];
    int min_visitors, max_visitors;
    printf("Inserisci nome guida: ");
    scanf("%s", name);
    printf("Inserisci numero minimo visitatori: ");
    scanf("%d", &min_visitors);
    printf("Inserisci numero massimo visitatori: ");
    scanf("%d", &max_visitors);

    snprintf(buffer, BUF_SIZE, "GUIDA:%s %d %d", name, min_visitors, max_visitors);
    send(sockfd, buffer, strlen(buffer) + 1, 0);

    printf("Guida registrata con successo!\n");

    close(sockfd);
    return 0;
}