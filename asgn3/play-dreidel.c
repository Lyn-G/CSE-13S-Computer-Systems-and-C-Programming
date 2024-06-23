#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include "mtrand.h"
#include "dreidel.h"

#define OPTIONS "p:c:s:v"

char* abc[8] = {
"Aharon",
"Batsheva",
"Chanah",
"David",
"Ephraim",
"Faige",
"Gamaliel",
"Hannah"
};

int coin_array[8] = {
0,
0,
0,
0,
0,
0,
0,
0
};

int printing_loss = 1;

int main(int argc, char **argv) {

	int player = 4;
	int player_number;
	
	int coins = 3;
	int coinings;
	
	uint64_t seed = 613;
	
	int round = 1;
	
	int r;
	
	while ((r = getopt (argc, argv, OPTIONS)) != -1) {
		switch (r) {
			case 'p':
				player_number = atoi(optarg);
				if (player_number > 8 || player_number < 2)  {
					exit(1);
					}
				else {
					player = player_number;
					}
				break;
			case 'c':
				coinings = atoi(optarg);
				if ((coinings > 20) || (coinings < 1))  {
					exit(1);
					}
				else {
					coins = coinings;
					}
				break;
			case 's':
				seed = atoi(optarg);
				if (seed < 1) {
					exit(1);
					}
				break; 
			case 'v':
				printing_loss = 0;
				break; 
			case '?':
				exit(1);
				
			}
	}
	
	mtrand_seed(seed);
	int winner = play_game(player , coins , &round);
	printf("%s %d %d %d %ld\n" , abc[winner] , player, coins, round, seed);
}
