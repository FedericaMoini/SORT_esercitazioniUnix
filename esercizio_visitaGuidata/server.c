#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "list.h"

#define BUF_SIZE 1000
#define PORT 8000

GuideNode* guideList = NULL;
VisitorNode* visitorList = NULL;

int main(){
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Errore opening socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        perror("Error on binding");
        exit(1);
    }

    listen(sockfd, 20);

    while(1){
        printf("Waiting for connections...\n");
        socklen_t cli_size = sizeof(cli_addr);
        int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_size);
        if(newsockfd == -1){
            perror("Error on accept");
            continue;
        }

        char buf[BUF_SIZE];
        recv(newsockfd, buf, BUF_SIZE, 0);
        printf("Ricevuto: %s\n", buf);

        if(strncmp(buf, "GUIDA:", 6) == 0){
            Guide newGuide;
            sscanf(buf + 6, "%s %d %d", newGuide.name, &newGuide.min_visitors, &newGuide.max_visitors);
            newGuide.current_visitors = 0;
            guideList = addGuide(guideList, newGuide);
            printf("Guida %s registrata (Min: %d, Max: %d).\n", newGuide.name, newGuide.min_visitors, newGuide.max_visitors);
            send(newsockfd, "Guida registrata", 16, 0);
        } else if(strncmp(buf, "VISITATORE:", 11) == 0){
            int num;
            sscanf(buf + 11, "%d", &num);
            visitorList = addVisitor(visitorList, (VisitorGroup){num});
            GuideNode* bestGuide = findGuide(guideList, num);
            
            if(bestGuide){
                bestGuide->guide.current_visitors += num;
                send(newsockfd, bestGuide->guide.name, strlen(bestGuide->guide.name) + 1, 0);
                printf("Gruppo di %d visitatori assegnato alla guida %s\n", num, bestGuide->guide.name);
            } else{
                send(newsockfd, "NESSUNA GUIDA DISPONIBILE", 25, 0);
                printf("Nessuna guida disponibile %d visitatori\n", num);
            }
        }

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}