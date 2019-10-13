// #ifndef GOFISH_H
// #define GOFISH_H

#include <stdlib.h>
#include <stdio.h>
#include "gofish.h"
#include "card.h"
#include "deck.h"
#include "player.h"

// void play_game();
// int user_turn(struct player* user, struct player* computer);
// int computer_turn(struct player* user, struct player* computer);
// int check_winner(struct player* user, struct player* computer);

int main(int args, char* argv[]) {
	//fprintf(stdout, "Put your code here.");
	/* initialize game */

	play_game();

}
void play_game() {
	//int turn = rand() % 2; //rand number to determine who plays first
	int turn = 0; // computer goes first
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
		game_finished = check_winner(user, computer);
		if (game_finished == 1) {
			break;
		}
		if (turn == 0) { // user's term
			turn = user_turn(user, computer);
		}
		else { // computer's term
			turn = computer_turn(user, computer);
		}
	}
}

int user_turn(struct player* user, struct player* computer) { // user plays
	draw_3_cards(user);
	char rank = user_play(user); // obtain valid rank request
	int boo = transfer_cards(computer, user, rank); //check is target rank is found
	if (boo != 0) { // if target rank is found
		printf("   -Player 2 gave you %i cards of rank %c\n", boo, rank);
		check_add_book(user, rank);
		printf("   -Player 1's turn\n\n\n");
		return 0;
	}
	else {
		printf("   -Player 2 has no %c's, Go Fish\n", rank);
		struct card temp = next_card();
		add_card(user, temp);
		check_add_book(user, rank);
		printf("   -Player 1 fished %c%c\n", temp.suit, temp.rank);
		if(temp.rank == rank) { // if card is of the same book
			printf("   -Player 1's turn\n\n\n");
			return 0; // user go again
		}
	}
	printf("   -Player 2's turn\n\n\n");
	return 1;
}
/*
computer plays its turn,
*/
int computer_turn(struct player* user, struct player* computer) {
	draw_3_cards(computer);
	char rank = computer_play(computer); // obatain valid rank request
	int boo = transfer_cards(user, computer, rank); // check if target rank is found
	if (boo != 0){ // if target rank is found
		printf("   -Player 1 gave %i cards of rank %c to player 2\n", boo, rank);
		check_add_book(computer, rank);
		printf("   -Player 2's turn\n\n\n");
		return 1;
	}
	else {
		struct card temp = next_card();
		add_card(computer, temp);
		check_add_book(user, rank);
		if (temp.rank == rank) {
			printf("   -Player 2 fished %c%c\n   -Player 2's turn\n\n\n", temp.suit, rank);
			return 1;
		} // else, term is compl
		printf("  -Player 1's turn\n\n\n");
		return 0;
	}
}
/*
prints play 1 hand, player 1 book, and player 2 book
also announces the winner and decide to play again if there is a winner
*/
int check_winner(struct player* user, struct player* computer) {
	print_hand(user);
	print_hand(computer);
	printf("Player 1's books- ");
	for (int i = 0; i<user->book_index; i ++) {
		printf("%c ", user->book[user->book_index]);
	}
	printf("\nPlayer 2's books- ");
	for (int i = 0; i<computer->book_index; i ++) {
		printf("%c ", computer->book[user->book_index]);
	}
	printf("\n");
	char play;
	// int i = 1;
	// if (i == 1) {
	if(game_over(user) == 1) {
		printf("Player 1 wins!\n");
		printf("Do you want to play again [Y/N]:\n");
		scanf(" %c", &play);
		if (play == 'Y') {
			printf("\n\n -----NEW GAME-----");
			play_game();
		}
		else {
			printf("Exiting.\n");
			return 1;
		}
	}
	if(game_over(computer) == 1) {

		printf("player 2 wins!\n");
		printf("Do you want to play again [Y/N]:\n");
		scanf(" %c", &play);
		if (play == 'Y') {
			printf("\n\n  -----NEW GAME-----");
			play_game();
		}
		else {
			printf("Exiting.\n");
			return 1;
		}
	}
	return 0;
}
//#endif