#ifndef GOFISH_H
#define GOFISH_H

#include <stdlib.h>
#include <stdio.h>
#include "gofish.h"
#include "card.h"
#include "deck.h"
#include "player.h"

void play_game();
void user_turn(struct player* user, struct player* computer);
void computer_turn(struct player* user, struct player* computer);
void check_winner(struct player* user, struct player* computer);
int main(int args, char* argv[]) {
	//fprintf(stdout, "Put your code here.");
	/* initialize game */
	//initialize deck

	play_game();

}
void play_game() {
	int turn = rand() % 2; //rand number to determine who plays first
	printf("Shuffling deck...\n");
	shuffle();
	//initialize players
	struct player* user = (struct player*)malloc(sizeof(struct player));
	struct player* computer = (struct player*)malloc(sizeof(struct player));
	deal_player_cards(user);
	deal_player_cards(computer);
	// initialize the state of the game
	int game_finished = 0;
	// initialize some saved game variables
	// char rank = '0';
	// struct card* temp_card = (struct card*)malloc(sizeof(struct card)); // declare temp
	// play the game
	while(game_finished == 0) {
		if (turn == 0) { // user's term
			user_turn(user, computer);
			turn = 1;
		}
		else { // computer's term
			computer_turn(user, computer);
			turn = 0;
		}
	}
}

void user_turn(struct player* user, struct player* computer) { // user plays
	check_winner(user, computer);
	char rank = user_play(user); // obtain valid rank request
	int boo = transfer_cards(user, computer, rank); //check is target rank is found
	if (boo != 0) { // if target rank is found
		//int card_num = transfer_cards(user, computer, rank);
		//printf("Player 2 gave you %i cards of rank %c\n", card_num, rank);
		printf("Request another card");
		check_add_book(user, rank);
	}
	else {
		printf("Computer tells to Go Fish\n");
		struct card temp = next_card();
		add_card(user, temp);
		if(temp.rank == rank) { // if card is of the same book
			printf("You fished %c, request another card\n", rank);
			user_turn(user, computer); // user go again
		}
		else {
			printf("you fished %c\n", temp.rank);
		}
	}
}

void computer_turn(struct player* user, struct player* computer) {
	check_winner(user, computer);
	char rank = computer_play(computer); // obatain valid rank request
	int boo = transfer_cards(computer, user, rank); // check if target rank is found
	if (boo != 0){ // if target rank is found
		//int card_num = transfer_cards(computer, user, rank);
		//printf("Computer requests you %c and you gave him %i\n cards of rank %c\n", rank, card_num, rank);
		check_add_book(user, rank);
		computer_turn(user, computer); // computer go again
	}
	else {
		//printf("Computer requests %c, you do not have the rank, computer draws card from the deck\n");
		struct card temp = next_card();
		add_card(computer, temp);
		if (temp.rank == rank) {
			//printf("computer draws a card of the requested rank. Computer gets another turn.\n")
			computer_turn(user, computer); //computer goes again
		} // else, term is complete
	}
}

void check_winner(struct player* user, struct player* computer) {
	printf("Player 1 books:\n");
	printf("Player 2 books:\n");
	char play;
	if(game_over(user)) {
		printf("Player 1 wins!\n");
		printf("Do you want to play again [Y/N]:\n");
		scanf(" %c", &play);
		if (play == 'Y') {
			play_game();
		}
		else {
			printf("Exiting.\n");
		}
	}
	if(game_over(computer)) {
		printf("player 2 wins!\n");
		printf("Do you want to play again [Y/N]:\n");
		scanf(" %c", &play);
		if (play == 'Y') {
			play_game();
		}
		else {
			printf("Exiting.\n");
		}
	}
}
#endif