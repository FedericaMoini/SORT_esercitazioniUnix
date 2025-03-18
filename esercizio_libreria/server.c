#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "list.h"

#define PORT 8000
#define BUF_SIZE 100

int main(){
    LIST inventory = NULL;
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 20);
    socklen_t cli_len = sizeof(cli_addr);

    while(1){
        int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
        char buf[BUF_SIZE];
        recv(newsockfd, buf, BUF_SIZE, 0);
        char* type = strtok(buf, "|");
        char* title = strtok(NULL, "|");
        
        if(strcmp(type, "C") == 0){
            Book new_book;
            strcpy(new_book.title, title);
            new_book.quantity = atoi(strtok(NULL, "|"));
            inventory = EnqueueOrdered(inventory, new_book);
            PrintList(inventory);
        } else if(strcmp(type, "L") == 0){
            Book* book = Find(inventory, title);
            if(book && book->quantity > 0){
                book->quantity--;
                if(book->quantity == 0){
                    inventory = Dequeue(inventory, title);
                }
                send(newsockfd, "OK", 3, 0);
            } else{
                send(newsockfd, "WAIT", 5, 0);
            }
        }
        close(newsockfd);
    }
    close(sockfd);
    return 0;
}