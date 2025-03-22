#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "list.h"

#define PORT 8000
#define BUF_SIZE 100

int main(){
    LIST market = NULL;
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 10);

    socklen_t cli_len = sizeof(cli_addr);

    while(1){
        int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
        char buf[BUF_SIZE];
        recv(newsockfd, buf, BUF_SIZE, 0);

        char* type = strtok(buf, "|");
        char* name = strtok(NULL, "|");

        /* Agente*/
        if(strcmp(type, "A") == 0){
            Stock new_stock;
            strcpy(new_stock.name, name);
            new_stock.quantity = atoi(strtok(NULL, "|"));
            new_stock.price = atoi(strtok(NULL, "|"));
            new_stock.min_price = atoi(strtok(NULL, "|"));
            new_stock.total_revenue = 0;
            market = EnqueueOrdered(market, new_stock);
            PrintList(market);
        } /* Investitore */
        else if(strcmp(type, "I") == 0){
            PrintList(market);
            char* target = strtok(NULL, "|");
            Stock* stock = Find(market, target);

            if(stock && stock->quantity > 0){
                stock->quantity--;
                stock->price++;
                stock->total_revenue += stock->price;

                if(stock->quantity == 0 || stock->price < stock->min_price){
                    market = Dequeue(market, stock->name);
                }
                send(newsockfd, "ACQUISTATO", 11, 0);
            } else {
                send(newsockfd, "NON DISPONIBILE", 16, 0);
            }
        }
        close(newsockfd);
    }
    close(sockfd);
    return 0;
}