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
	struct player user;
	struct player computer;
	deal_player_cards(human);
	deal_player_cards(computer);
	// initialize the state of the game
	int game_finished = 0;
	// turn
	while(game_finished == 0) {
		if (turn == 0) {
			user_play(user);
		}
		else {
			computer_play(computer);
		}
	}
}
