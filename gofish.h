#ifndef GOFISH_H
#define GOFISH_H
#include "player.h"
#include "deck.h"
#include "card.h"
/*
   Define any prototype functions
   for gofish.h here.
*/
void play_game();
int user_turn(struct player* user, struct player* computer);
int computer_turn(struct player* user, struct player* computer);
int check_winner(struct player* user, struct player* computer);

#endif
