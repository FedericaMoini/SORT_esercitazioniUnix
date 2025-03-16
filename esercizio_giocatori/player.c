#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUF_SIZE 256

int main() {
	int sockfd;
	struct sockaddr_in serv_addr;
	char buf[BUF_SIZE];

	// Socket creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("Errpre apertura socket");
		exit(1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("Errore connessione");
		exit(1);
	}

	// Send player name
	printf("Inserisci il tuo nome: ");
	fgets(buf, BUF_SIZE, stdin);
	buf[strcspn(buf, "\n")] = 0;
	send(sockfd, buf, strlen(buf) + 1, 0);

	// Receive result
	recv(sockfd, buf, BUF_SIZE, 0);
	printf("Risultato: %s\n", buf);

	close(sockfd);
	return 0;
}
