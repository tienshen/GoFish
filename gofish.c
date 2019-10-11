#include <stdio.h>

int main(int args, char* argv[]) 
{
	//fprintf(stdout, "Put your code here.");
	/* initialize game */
	int play_no_more = 0;
	while (play_no_more == 0){ //player plays
		play_game();
		// player 1 plays

		// check for books

		// player 2 plays

		// check for books

		// check game is finished

		// if game is finished, say who won the game

		// ask the player if he wishes to play again

		// if so, start the game
	}
}
int play_game() {
	//initialize deck
	int turn = rand() % 2; //rand number to determine who plays first
	shuffle();
	//initialize players
	struct player* user;
	struct player* computer;
	deal_player_cards(user);
	deal_player_cards(computer);
	// initialize the state of the game
	int game_finished = 0;
	// initialize some saved game variables
	char rank = '0';
	int boo; // boolean for if card a card is found from hand
	int card_num; // keep number of cards transferd
	struct card* temp_card = (struct card*)malloc(sizeof(struct card)); // declare temp
	// turn
	while(game_finished == 0) {
		if (turn == 0) { // user's term
			rank = user_play(user);
			boo = search(computer, rank);
			if (boo) {
				card_num = transfer_cards(user, computer, rank);
				printf("Computer gave you %i cards of rank %c\n", card_num, rank)
				printf("Request another card")
				check_add_book(user, rank);
				turn = (turn+1);
			}
			else {
				printf("Computer says: Go Fish\n");
				temp = next_card();
				add_card(user, temp);
			}
		}
		else { // computer's term
			rank = computer_play(computer);
			boo = search(user, rank);
			if (boo){

			}
		}
		turn = (turn+1) % 2; //change state of turn
	}

}

int play_turn(struct player* src, struct player* dest, int turn) {

}