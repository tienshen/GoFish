#ifndef GOFISH_H
#define GOFISH_H

/*
   Define any prototype functions
   for gofish.h here.
*/
void play_game();
void user_turn(struct player* user, struct player* computer);
void computer_turn(struct player* user, struct player* computer);
void check_winner(struct player* user, struct player* computer);

#endif
