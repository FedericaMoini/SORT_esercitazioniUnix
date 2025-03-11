#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <netdb.h>
#include <time.h>
#include <sys/wait.h>


#define BUF_SIZE 1000
// Definition of number of child prcesses to be created
#define NUM_CLIENTS 5


char *host_name = "127.0.0.1"; /* local host */
int port = 8000;


int main(int argc, char *argv[]) 
{
	struct sockaddr_in serv_addr;
 	struct hostent* server;	
	
	if (argc < 2) { 
		printf("Usage: %s integer\n", argv[0]);
		exit(-1);
	}
	int num = atoi(argv[1]);
	
	
	if ( ( server = gethostbyname(host_name) ) == 0 ) 
	{
		perror("Error resolving local host\n");
		exit(1);
	}
	
	// Creting NUM_CLIENTS child processes
	for(int i = 0; i< NUM_CLIENTS; i++){
		pid_t pid = fork();
		if(pid == 0){ // child process
			srand(time(NULL) + getpid()); // Random seed initialization for each child
			int num = rand() % 100; // Random number generation
			int answer;
			
			bzero(&serv_addr, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = ((struct in_addr *)(server->h_addr))->s_addr;
			serv_addr.sin_port = htons(port);
			
			int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
			if ( sockfd == -1 ) {
				perror("Error opening socket\n");
				exit(1);
			}

			if ( connect(sockfd, (void*)&serv_addr, sizeof(serv_addr) ) == -1 ) {
				perror("Error connecting to socket\n");
				exit(1);
			}
			
			printf("[Child %d] Send the number %d\n", getpid(), num);
			
			/* This sends the string plus the string terminator '\0' */
			if ( send(sockfd, &num, sizeof(num), 0) == -1 ) {
				perror("Error on send\n");
				exit(1);
			}
			
			printf("[Child %d] Waiting response \n", getpid());
	
			if ( recv(sockfd, &answer, sizeof(answer), 0) == -1 ) {
				perror("Error in receiving response from server\n");
				exit(1);
			}
			
			printf("[Child %d] Response: Sent %d, Received %d\n", getpid(), num, answer);

			close(sockfd);
			exit(0);
		}
		sleep(1); // Delay creation of next process to avoid overlapping prints
	}
	
	// Wait for all children to be terminated
	for ( int i = 0; i < NUM_CLIENTS; i++){
		wait(NULL);
	}


	return 0;
}



