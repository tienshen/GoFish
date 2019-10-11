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
			user_turn();
		}
		else { // computer's term
			rank = computer_play(computer);
			boo = search(user, rank);
			if (boo){

			}
		}
		//turn = (turn+1) % 2; //change state of turn
	}
}
int user_turn() { // user plays
	rank = user_play(user); // obtain valid rank request
	boo = search(computer, rank); //check is target rank is found
	if (boo) { // if target rank is found
		card_num = transfer_cards(user, computer, rank);
		printf("Computer gave you %i cards of rank %c\n", card_num, rank);
		printf("Request another card");
		check_add_book(user, rank);
		turn = (turn+1);
	}
	else {
		printf("Computer says: Go Fish\n");
		temp = next_card();
		if(temp->rank == rank) { // if card is of the same book
			printf("You fished %c, request another card\n", rank);
			add_card(user, temp);
			user_turn(); // user go again
		}
		else {
			printf("you fished %c", temp->rank);
			add_card(user, temp); 
		}
	}
	return 1;
}

int computer_turn() {
	rank = computer_play(computer); // obatain valid rank request
	boo = search(user, rank); // check if target rank is found
	if (boo){ // if target rank is found

	}
}

int check winner() {
	
}