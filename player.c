
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "player.h"
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
	printf("\nPlayer 1's hand- ");
	for (int i = 0; i < target->hand_size; i++) {
		printf("%c%c ", temp->top.suit, temp->top.rank);
		temp = temp->next;
	}
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
	new_hand->top = new_card;
	if (target->hand_size == 0) { // if hand is empty, new card is assigned top card
		target->card_list = new_hand; 
		target->hand_size++;
	}
	else { // if there are cards in the hand, top becomes the new card
		new_hand->next = target->card_list;
		target->card_list = new_hand;
		target->hand_size++;
	}
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
	if (first->top.rank == old_card.rank) {
		first = first->next;
	}
	while(first != NULL) {
		if (first->top.rank == old_card.rank) {
			prev->next = first->next;
		}
		prev = first;
		first = first->next;
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

char check_add_book(struct player* target, char rank) {
	int i = 0;
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	temp = target->card_list; // save current card in temp
	//utilize first loop to check if there is a book
	while (temp != NULL) { // check temp is the target card
		if (target->card_list->top.rank == rank) { //
			i++; // increment count
			temp = temp->next;
		}
	}
	if (i >= 4) { // if a book is found, rank is added
		target->book[target->book_index] = rank;
		target->book_index++;
		// second loop removes if a book is found
		temp = target->card_list;
		while (temp != NULL) { // check temp is the target card
			if (target->card_list->top.rank == rank) { //
				i++; // increment count
				remove_card(target, temp->top); //
				temp = temp->next;
			}
			return rank;
		}
	}
	return '0';
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
	int boo = search(src, rank); //determine if player had the card
	if (!boo) { // if boo = 0, return 0
		return boo;
	}
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	temp = src->card_list; // I modified the search method to make transfer method
	while (temp != NULL) {
		if (temp->top.rank == rank) {
			remove_card(src, temp->top); // remove card from src
			add_card(dest, temp->top); // add card to dest
		}
		temp = temp->next;
	}
	return boo;
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
	int x = rand() % (target->hand_size+1); // return any value between 0 - handsize
	struct hand* temp = (struct hand*)malloc(sizeof(struct hand));
	temp = target->card_list; // get top card
	for (int i = 0; i < x; i++){ // loop through the hand to get to the card of desired index
		temp = temp->next;
	}
	return temp->top.rank; // return the rank
}

/* 
 * Function: user_play
 * -------------------
 *
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
	int boo=0;
	while(boo == 0) {
		printf("\nPlayer 1's turn, enter a Rank: ");
		scanf(" %c", &input);
		boo = search(target, input);
		if(boo == 0)
			printf("Error - must have at least one card from rank to play");
	}
	return input;}

