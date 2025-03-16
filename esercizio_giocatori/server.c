#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include "list.h"

#define PORT 12345
#define BUF_SIZE 256
#define MAX_PLAYERS 3

LIST registered_players;
LIST connected_players;

int main(){
	int sockfd, newsockfd;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	char buf[BUF_SIZE];

	srand(time(NULL));

	// List creation
	registered_players = NewList();
	connected_players = NewList();

	// Socket creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("Errore apertura socket");
		exit(1);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("Errore binding");
		exit(1);
	}

	listen(sockfd, 5);
	printf("Server in ascolto sullla porta %d...\n", PORT);

	while (1) {
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
		if (newsockfd < 0) {
			perror("Errore accept");
			continue;
		}

		// Receive player name
		recv(newsockfd, buf, BUF_SIZE, 0);
		printf("Giocatore connesso: %s\n", buf);

		// Player creation
		Player new_player;
		strcpy(new_player.name, buf);
		new_player.games_played = 0;
		new_player.score = 0;

		// Player registration
		Player* found = Find(registered_players, buf);
		if (found == NULL) {
			registered_players = EnqueueLast(registered_players, new_player);
		}

		connected_players = EnqueueLast(connected_players, new_player);
		printf("Giocatori connessi: %d\n", getLength(connected_players));

		// If the number of players is sufficient, start the game
		if (getLength(connected_players) >= MAX_PLAYERS) {
			printf("Inizio Partita!\n");

			LIST temp = connected_players;
			int pos = 0;
			while (temp != NULL) {
				if (pos == 0) temp->player.score += 3;
				else if (pos == 1) temp->player.score += 2;
				else if (pos == 2) temp->player.score +=1;

				temp->player.games_played++;
				temp = temp->next;
				pos++;
			}

			// Send results to players
			temp = connected_players;
			while (temp != NULL) {
				sprintf(buf, "Partita conclusa! %s: %d punti, %d partite",
					temp->player.name, temp->player.score, temp->player.games_played);
				send(newsockfd, buf, strlen(buf) + 1, 0);
			}

			// Reset connected players list
			connected_players = DeleteList(connected_players);
		}
		close(newsockfd);
	}
	close(sockfd);
	return 0;
}
