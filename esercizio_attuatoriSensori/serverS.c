#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "list.h"

#define BUF_SIZE 1000
#define PORT 8000

typedef struct{
    int sockfd;
    char name[30];
} Actuator;

LIST actuators = NULL;
void registerActuator(int sockfd, char* name){
    Actuator new_actuator;
    new_actuator.sockfd = sockfd;
    strcpy(new_actuator.name, name);
    
    ItemType new_item;
    new_item.value = (double)(intptr_t)&new_actuator;

    actuators = EnqueueLast(actuators, new_item);
    printf("Actuator '%s' registered.\n", name);
}

void sendSensorDataToActuators(char* data){
    LIST tmp = actuators;
    while(tmp != NULL){
        Actuator* actuator = (Actuator*)(intptr_t)tmp->item.value;
        send(actuator->sockfd, data, strlen(data), 0);
        tmp = tmp->next;
    }
}

int main(){
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t address_size = sizeof(cli_addr);
    char buf[BUF_SIZE];

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Error opening socket");
        exit(1);
    }

    int options = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(options)) < 0){
        perror("Error on setsockopt");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        perror("Error on binding");
        exit(1);
    }

    if(listen(sockfd, 20) == -1){
        perror("Error on listen");
        exit(1);
    }

    while(1){
        printf("Waiting for a new connection...\n");

        int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &address_size);
        if(newsockfd == -1){
            perror("Errore on accept");
            exit(1);
        }

        memset(buf, 0, BUF_SIZE);
        if(recv(newsockfd, buf, BUF_SIZE, 0) == -1){
            perror("Error on receive");
            exit(1);
        }

        printf("Actuator '%s' connected.\n", buf);
        registerActuator(newsockfd, buf);

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}