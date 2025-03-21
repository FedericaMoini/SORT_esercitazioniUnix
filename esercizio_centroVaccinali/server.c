#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "list.h"

#define PORT 8000
#define BUF_SIZE 100

int main(){
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 20);
    socklen_t cli_len = sizeof(cli_addr);

    LIST centers = NULL;
    LIST suppliers = NULL;

    while(1){
        int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
        char buf[BUF_SIZE];
        recv(newsockfd, buf, BUF_SIZE, 0);
        char* type = strtok(buf, "|");
        char* name = strtok(NULL, "|");

        if(strcmp(type, "F") == 0){
            int supply = atoi(strtok(NULL, "|"));
            int min_demand = atoi(strtok(NULL, "|"));

            Supplier* new_supplier = (Supplier*)malloc(sizeof(Supplier));
            strcpy(new_supplier->name, name);
            new_supplier->supply = supply;
            new_supplier->min_demand = min_demand;
            suppliers = EnqueueOrdered(suppliers, new_supplier, 1);
            PrintSuppliers(suppliers);
        } else if(strcmp(type, "C") == 0){
            int demand = atoi(strtok(NULL, "|"));
            
            Center* new_center = (Center*)malloc(sizeof(Center));
            strcpy(new_center->name, name);
            new_center->demand = demand;centers = EnqueueOrdered(centers, new_center, 0);
            PrintCenters(centers);
        }

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}