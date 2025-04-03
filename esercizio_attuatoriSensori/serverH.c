#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

// #define BUF_SIZE 1000
#define PORT 9000

void sendDataToActuators(char* data){
    int sockfd;
    struct sockaddr_in serv_addr;
    // char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
    serv_addr.sin_port = htons(8000);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        perror("Error connecting to server");
        exit(1);
    }

    if(send(sockfd, data, strlen(data), 0) == -1){
        perror("Error on send");
        exit(1);
    }

    printf("Sensor data sent to actuators\n");
    close(sockfd);
}

int main(){
    char sensor_data[] = "Temperature: 22°C";
    sendDataToActuators(sensor_data);
    return 0;
}