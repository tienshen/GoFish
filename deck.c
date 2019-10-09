#include "deck.h"
#include "stdlib.h"
#include "stdio.h"

// int i, j, k;
int size = 52;

// test code here
int main() {
	shuffle();
}
/*
 * Function: shuffle
 * --------------------
 *  Initializes deck_instance and shuffles it.
 *  Resets the deck if a prior game has been played.
 * 
 *  returns: 0 if no error, and non-zero on error
 */ 

int shuffle()
{

	int k = 0;
	char ranks[14] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A', '\0'}; // initialize arrays to fill in the deck
	char suits[5] = {'C', 'D', 'S', 'H', '\0'};
	for (int i = 0; i< 13; i++){
		for (int j =0; j< 4; j++){
			deck_instance.list[k].suit = suits[j];
			deck_instance.list[k].rank = ranks[i];
			k ++;
		}
	}

	// shuffle the deck with fisher-yates shuffle
	// //srand (time(NULL)); 
	for (k = size - 1; k > 0; k--) {
		int x = rand() % (k+1); // random integer betwen 0 and 52
		struct card temp = deck_instance.list[k]; // temp for storing card at k
		deck_instance.list[k] = deck_instance.list[x]; // the following 2 lines swap the two cards
		deck_instance.list[x] = temp;
	}
	for (k = 0; k < 52; k++){
		printf("rank is: %c, character = %c\n", deck_instance.list[k].suit, deck_instance.list[k].rank);
	}
}

/*
 * Function: deal_player_cards
 * ---------------------------
 *  Deal 7 random cards to the player specified in the function.
 *  Remove the dealt cards from the deck. 
 *
 *  target: pointer to the player to be dealt cards
 *
 *  returns: 0 if no error, and non-zero on error
 */

int deal_player_cards(struct player* target)
{
	int i;
	for (i = 0; i > 7; i++) {
		target.add_card(deck_instance.next_card()); //removes a card from the top of the deck 
	}
}

/*
 * Function: next_card
 * -------------------
 *  Return a pointer to the top card on the deck.
 *  Removes that card from the deck. 
 *
 *  returns: pointer to the top card on the deck.
 */

struct card* next_card( ){

}
/*
 * Function: size
 * --------------
 *  Return the number of cards left in the current deck.
 *
 *  returns: number of cards left in the deck.
 */
size_t deck_size( ) {
	return deck_instance.top_card;
}
