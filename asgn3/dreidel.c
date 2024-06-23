#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "dreidel.h"
#include "mtrand.h"

#define OPTIONS "p:c:s:v"
int player_number;


char spin_dreidel(void) {
	int n = mtrand_rand64() % 4;

return n;
}

char spinning_the[] = {
'G',
'H',
'N',
'S'
};
	
	int play_game (int n_players , int coins_per_player , int * n_rounds) {
	
	int player = n_players - 1;
	int still_in = 0;
	
	int pot = 0;
	int taking_half_pot = 0;

	int done_spinning;
	
	int answer;
	
	for (int starting = 0; starting < (n_players); starting = starting + 1) {
					coin_array[starting] = coins_per_player;
					}
	for (int i = n_players; i < 9; i = i + 1) {
				coin_array[i] = -1;
				}
	
	while (player != 0) {
		
		if (still_in == 8) {
			still_in = 0;
			* n_rounds = * n_rounds + 1;
				 
			}
		else {
			if (coin_array[still_in] == -1) {
				if (still_in == 8) {
					still_in = 0;
					* n_rounds = * n_rounds + 1;
					}
				else {
					still_in = still_in + 1;
					}
				}
			else if (coin_array[still_in] != -1) {
				done_spinning = spin_dreidel();
					//printf("player: %s , coins: %d , pot: %d, round: %d\n" , abc[still_in] , coin_array[still_in] , pot , *n_rounds);
				//printf("spin face: %d\n\n" , done_spinning);
				if (done_spinning == 0) {
					coin_array[still_in] = pot + coin_array[still_in];
					pot = 0;
					still_in = 1 + still_in;
					}
				else if (done_spinning == 1) {
					taking_half_pot = pot / 2;
					pot = pot - taking_half_pot;
					coin_array[still_in] = taking_half_pot + coin_array[still_in];
					still_in = 1 + still_in;
					taking_half_pot = 0;
					}
				else if (done_spinning == 2) {
					still_in = 1 + still_in;
					}
				else if (done_spinning == 3) {
					if (coin_array[still_in] == 0) {
						coin_array[still_in] = -1;
						if (printing_loss == 0) {
							printf("%s" , abc[still_in]);
							printf(": elmininated in round ");
							printf("%d " , * n_rounds);
							printf("of a ");
							printf("%d " , n_players);
							printf("player game.\n");
							}
						still_in = 1 + still_in;
						player = player - 1;
					}
					else {
						pot = pot + 1;
						coin_array[still_in] = coin_array[still_in] - 1;
						still_in = 1 + still_in;
						}
					}	
				}
		 
			}
	
		}
for (int k = 0; k < 8; k = k + 1) {
        if (coin_array[k] != -1) {
            answer = k;
            }
        }
	
return answer;
}

