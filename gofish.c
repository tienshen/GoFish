#ifndef GOFISH_H
#define GOFISH_H

#include <stdio.h>
#include "card.h"
#include "deck.h"
#include "player.h"

void play_game();
void user_turn(struct player* user, struct player* computer);
void computer_turn(struct player* user, struct player* computer);
int check_winner(struct player* user, struct player* computer);
//int main(int args, char* argv[]) 
int main(void) {
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
	struct player* user;
	struct player* computer;
	deal_player_cards(user, computer);
	deal_player_cards(user, computer);
	// initialize the state of the game
	int game_finished = 0;
	// initialize some saved game variables
	// char rank = '0';
	// struct card* temp_card = (struct card*)malloc(sizeof(struct card)); // declare temp
	// play the game
	while(game_finished == 0) {
		if (turn == 0) { // user's term
			user_turn(user);
			turn = 1;
		}
		else { // computer's term
			computer_turn(computer);
			turn = 0;
		}
	}
}

void user_turn(struct player* user, struct player* computer) { // user plays
	check_winner(user, computer);
	char rank = user_play(user); // obtain valid rank request
	boo = search(computer, rank); //check is target rank is found
	if (boo) { // if target rank is found
		card_num = transfer_cards(user, computer, rank);
		printf("Player 2 gave you %i cards of rank %c\n", card_num, rank);
		printf("Request another card");
		check_add_book(user, rank);
		return 0;
	}
	else {
		printf("Computer tells to Go Fish\n");
		temp = next_card();
		add_card(user, temp);
		if(temp->rank == rank) { // if card is of the same book
			printf("You fished %c, request another card\n", rank);
			return 0; // user go again
		}
		else {
			printf("you fished %c\n", temp->rank);
		}
	}
	return 1;
}

// int computer_turn(struct player* user, struct player* computer) {
// 	check_winner();
// 	char rank = computer_play(computer); // obatain valid rank request
// 	boo = search(user, rank); // check if target rank is found
// 	if (boo){ // if target rank is found
// 		card_num = transfer_cards(computer, user, rank);
// 		printf("Computer requests you %c and you gave him %i\n cards of rank %c\n", rank, card_num, rank);
// 		check_add_book(user, rank);
// 		return 1;
// 	}
// 	else {
// 		printf("Computer requests %c, you do not have the rank, computer draws card from the deck\n");
// 		temp = next_card();
// 		add_card(computer, temp);
// 		if (temp->rank == rank) {
// 			printf("computer draws a card of the requested rank. Computer gets another turn.\n")
// 			return 1;
// 		} // else, term is complete
// 	}
// }

// int check_winner(struct player* user, struct player* computer) {
// 	printf("Player 1 books:\n");
// 	printf("Player 2 books:\n");
// 	if(game_over(user)) {
// 		printf("Player 1 wins!\n");
// 		printf("Do you want to play again [Y/N]:\n");
// 		scanf(" %c", &play);
// 		if (play == 'Y') {
// 			play_game();
// 		}
// 		else {
// 			printf("Exiting.\n");
// 		}
// 	}
// 	if(game_over(computer)) {
// 		printf("player 2 wins!\n");
// 		printf("Do you want to play again [Y/N]:\n");
// 		scanf(" %c", &play);
// 		if (play == 'Y') {
// 			play_game();
// 		}
// 		else {
// 			printf("Exiting.\n");
// 		}
// 	}
// }
#endif