#pragma once

extern char* abc[8];
extern int coin_array[];
extern int player_number;
extern int coins;
extern int printing_loss;
char spin_dreidel(void);
int play_game (int n_players , int coins_per_player , int * n_rounds);
