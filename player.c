
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "player.h"
#include "deck.h"
#include <stdio.h>

/*
 * Structure: player
 * -----------------
 *  Each player holds some number of cards in their hand
 *  Each player can have at most 7 "books" before winning 
 */

/* 
 * Instance Variables: user, computer
 * ----------------------------------
 *
 *  We only support 2 users: a human and a computer
 */
//struct player user;
//struct player computer;

void print_hand(struct player* target) {
	//printf("%i", target->hand_size);
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	temp = target->card_list; // get top card
	printf("Player 1's hand- ");
	for (int i = 0; i < target->hand_size; i++) {
		printf("%c%c ", temp->top.suit, temp->top.rank);
		temp = temp->next;
	}
	printf("\n");
}
/*
 * Function: add_card
 * -------------------
 *  Add a new card to the player's hand-> 
 *
 *  target: the target player
 *  new_card: pointer to the new card to add
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int add_card(struct player* target, struct card new_card)
{
	struct hand* new_hand = (struct hand *)malloc(sizeof(struct hand));
	new_hand->top = new_card; //put card in new hand
	new_hand->next = target->card_list; // new hand's next hand is the first hand
	target->card_list = new_hand; // first hand is now new hand
	target->hand_size++;
	return 0;
}
/*
 * Function: remove_card
 * ---------------------
 *  Remove a card from the player's hand-> 
 *
 *  target: the target player
 *  old_card: pointer to the old card to remove
 *
 *  returns: return 0 if no error, non-zero otherwise
   */
int remove_card(struct player* target, struct card old_card)
{
	struct hand* first = target->card_list;
	struct hand* prev = first;
	//check if old card is the first card in the hand and remove if so.
	if (target->card_list->top.rank == old_card.rank && target->card_list->top.suit == old_card.suit) {
		target->card_list = target->card_list->next;
		target->hand_size--;
	}
	//otherwise search through all
	else {
		while(first != NULL) {
			if (first->top.rank == old_card.rank && first->top.suit == old_card.suit) {
				prev->next = prev->next->next; // 1 links to 3
				prev = prev->next; // 1 is now 3
				if (prev == NULL) { // this keeps seg fault out when removing last card in the hand
					first = prev;
				}
				else {
					first = prev->next; // 2 is now 4, skips 3
				}
				target->hand_size--;
			}
			else{
				prev = first; //reset prev and next
				first = first->next;
			}
		}
	}
	return 0;
}
/*
 * Function: check_add_book
 * ------------------------
 *  Check if a player has all 4 cards of the same rank->
 *  If so, remove those cards from the hand, and add the rank to the book->
 *  Returns after finding one matching set of 4, so should be called after adding each a new card->
 * 
 *  target: pointer to the player to check
 *  
 *  Return: a char that indicates the book that was added; return 0 if no book added->
 */

void check_add_book(struct player* target, char rank) {
	int i = 0;
	int j = 0;
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	temp = target->card_list; // save current card in temp
	//utilize first loop to check if there is a book
	while (j < target->hand_size) { // check temp is the target card
		j++;
		if (temp->top.rank == rank) { //
			i++; // increment count
			temp = temp->next;
		}
	}
	if (i == 4) { // if a book is found, rank is added
		printf("   -Player books %c\n", rank);
		target->book[target->book_index] = rank;
		target->book_index++;
		// second loop removes if a book is found
		temp = target->card_list;
		j = 0;
		while (j < target->hand_size) { // check temp is the target card
			if (target->card_list->top.rank == rank) { //
				remove_card(target, temp->top); //
				temp = temp->next;
			}
			j++;
		}
	}
}


/*
 * Function: search
 * ----------------
 *  Search a player's hand for a requested rank->
 *  
 *  rank: the rank to search for
 *  target: the player (and their hand) to search
 *
 *  Return: If the player has a card of that rank, return 1, else return 0
 */
int search(struct player* target, char rank) // linear search implementation
{
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	temp = target->card_list; // save current card in temp
	while (temp != NULL) {
		if (temp->top.rank == rank) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

/*
 * Function: transfer_cards
 * ------------------------
 *   Transfer cards of a given rank from the source player's 
 *   hand to the destination player's hand-> Remove transferred
 *   cards from the source player's hand-> Add transferred cards
 *   to the destination player's hand->
 *   
 *   src: a pointer to the source player
 *   dest: a pointer to the destination player
 *   rank: the rank to transfer
 *
 *   Return: 0 if no cards found/transferred, <0 if error, otherwise 
 *   return value indicates number of cards transferred
 */ 
int transfer_cards(struct player* src, struct player* dest, char rank)
{
	int i = 0;
	if (search(src, rank) == 0) { // if boo = 0, return 0
		return i;
	}
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	temp = src->card_list; // I modified the search method to make transfer method
	while (temp != NULL) {
		if (temp->top.rank == rank) {
			add_card(dest, temp->top); // add card to dest
			remove_card(src, temp->top); // remove card from src
			i++;
		}
		temp = temp->next;
	}
	return i;
}

/*
 * Function: game_over
 * -------------------
 *   Boolean function to check if a player has 7 books yet
 *   and the game is over
 *
 *   target: the player to check
 *   
 *   Return: 1 if game is over, 0 if game is not over
 */
int game_over(struct player* target) { // empty the hand
	if (target->book_index == 6) {
		return 1;
	}
	else {
		return 0;
	}
}

/* 
 * Function: reset_player
 * ----------------------
 *
 *   Reset player by free'ing any memory of cards remaining in hand,
 *   and re-initializes the book->  Used when playing a new game->
 * 
 *   target: player to reset
 * 
 *   Return: 0 if no error, and non-zero on error->
 */
// int reset_player(struct player* target){
// 	target->hand_size = 0; //
// 	int i = deal_player_cards(target); //
// 	return i;
// }

/* 
 * Function: computer_play
 * -----------------------
 *   Select a rank randomly to play this turn-> The player must have at least
 *   one card of the selected rank in their hand->
 *   target: the player's hand to select from
 *   Rank: return a valid selected rank
 */
char computer_play(struct player* target){
	int i = target->hand_size;
	int x = rand() % (i+1); // return any value between 0 - handsize
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	temp = target->card_list; // get top card
	for (int i = 0; i < x; i++){ // loop through the hand to get to the card of desired index
		temp = temp->next;
	}
	printf("Player 2's turn, enter a Rank: %c\n", temp->top.rank);
	return temp->top.rank; // return the rank
}
/* 
 * Function: user_play
 * -------------------
 *   Read standard input to get rank user wishes to play->  Must perform error
 *   checking to make sure at least one card in the player's hand is of the 
 *   requested rank->  If not, print out "Error - must have at least one card from rank to play"
 *   and then re-prompt the user->
 *
 *   target: the player's hand to check
 * 
 *   returns: return a valid selected rank
 */
char user_play(struct player* target){
	char input;
	char line[128];
	int boo=0;
	while(boo == 0) {
		printf("Player 1's turn, enter a Rank: ");
		//scanf(" %c", &input);
		fgets(line, sizeof line, stdin); // scanf gave us problems when accidently enter more
		input = line[0];
		boo = search(target, input);
		if(boo == 0)
			printf("Error - must have at least one card from rank to play\n");
	}
	return input;
}

void draw_3_cards(struct player* target) {
	if (target->hand_size == 0){
		for (int i = 0; i<3; i++) {
			add_card(target, next_card());
		}
		printf("   -player ran out of cards, draw 3 cards");
	}
}
// int main(int args, char* argv[]) {
// 	//int turn = 0; // computer goes first
// 	printf("Shuffling deck...\n");
// 	shuffle();
// 	//initialize players
// 	struct player* user = (struct player*)malloc(sizeof(struct player));
// 	struct player* computer = (struct player*)malloc(sizeof(struct player));
// 	deal_player_cards(user);
// 	deal_player_cards(computer);
// 	print_hand(user);
// 	printf("p2 ");
// 	print_hand(computer);
// 	printf("test transfer_card\n");
// 	transfer_cards(user, computer, 'J');
// 	print_hand(user);
// 	printf("p2 ");
// 	print_hand(computer);
// 	// printf("\ntest remove card\n");
// 	// int i = remove_card(user, user->card_list->next->top);
// 	// // if (i != 1) {
// 	// 	print_hand(user);
// 	// 	printf("there are %i in the hand\n", user->hand_size);
// 	// }
// 	// printf("test add card\n");
// }