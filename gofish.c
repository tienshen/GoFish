#include <stdio.h>

int main(int args, char* argv[]) 
{
	//fprintf(stdout, "Put your code here.");
	/* initialize game */
	//initialize deck
	shuffle();
	//initialize players
	struct player human;
	struct player computer;
	deal_player_cards(human);
	deal_player_cards(computer);
	// initialize the state of the game
	int games_finished = 0;
	// turn

	while (games_finished == 0){ //player plays
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

int human_play() {}

int computer_play() {}