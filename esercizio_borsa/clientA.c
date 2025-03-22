#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    
    if (argc != 5) {
        printf("Usage: %s <Nome_Agente> <Quantità> <Prezzo Attuale> <Prezzo Minimo>\n", argv[0]);
        return 1;
    }
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

    char msg[BUF_SIZE];
    sprintf(msg, "ADD|%s|%s|%s|%s", argv[1], argv[2], argv[3], argv[4]);
    send(sockfd, msg, strlen(msg) + 1, 0);

    recv(sockfd, msg, BUF_SIZE, 0);
    printf("Il titolo è stato ritirato. Ricavo totale: %s\n", buffer);

    close(sockfd);
    return 0;
}