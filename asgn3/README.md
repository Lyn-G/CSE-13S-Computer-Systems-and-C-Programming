### Description of the Assignment

We are to write code that simulates a single game of dreidel.
The program will print out the name of the winning player along with the number of rounds it took to complete the game, where a
round is one pass through all of the remaining players. It will also print out the random number seed and the amount of players 
& coins that were in the game.


### How I Built It

I set many variables for the deault settings of the game if the player does not pass anything. If the player does pass something,
but it turns out to be incorrect, then the game will exit. I set the player names and their coins into an array to use for later.
The seed will be produced using the user's input (or default) along with the the Mersenne Twister code provided for us in 
asgn3-files.tgz. A function will call for the game to start! There will be a variable that will be used as an index for accessing
both the player and their corresponding place in the coin array. All players that aren't playing, or that are eliminated, will be
given -1 coins so that the if-statements knows to skip them in the loop when its their turn. The game is running entirely though a 
while-loop that has the condition to run only if the player amount isn't 0. The spin_dreidel function given to us will return a
return a number modulus 4 that simulates what face the dreidel will land on. Depending on what face it's on, these things will
happen for the player:

If 0 is returned, that corresponds to G. Add to the character amount with the pot’s amount. The pot will be 0 after. Add one to 
the indexing variable. 

If 1 is returned, that corresponds to H. Take half from the pot, rounding down. Add to the character amount with the half’s 
amount. The pot will be half after. Add one to the indexing variable. 

If 2 is returned, that corresponds to N. Do nothing, but add one to the indexing variable.

If 3 is returned, that corresponds to S. Put a coin in if one can, if not, eliminate them. Add one to the indexing variable. 
The variable that’s correlated with the amount of players still valid in the game will get subtracted for each person eliminated.

A round is counted once all valid players have gone. There is a "pot" variable that simulates where the players will put a coin in
if they need to. The index variable will be checked each time to make sure it doesn't go above the length of the arrays. It
will reset to 0 each time if it does.
The user can also set an option if they want to print out when a player is eliminated. The only way for a player to be eliminated
is when they have 0 coins and get the S face of dreidel. They will be given -1 coins from that point on, and the program will 
print out that they've been eliminated along with how many players were in the game and how many rounds they lasted.
Once there's only one valid player left in the game, a for-loop will access the coin array to find the index of the place that 
doesn't have -1 coins. Return that index number variable. The print-statement for the winner will use that index to announce the
winner, along with the other information.


### How to Run It

1. Compile the assignment files.
2. Run ./play-dreidel along with any of these commands (however, there's no need to, because there are defaults for each one).
-p: set the amount of players [2-8].
-c: set the amount of coins [1-20].
-s: set the seed.
-v: if the user wants to output when a player is eliminated.


### Bugs

I did not encounter any bugs, lest we count my own errors.


### Cite Sources

Resources that I used:
TAs and tutors helped me understand many new commands that I used in my program.

Online, I learned how to use [source](https://linuxize.com/post/bash-source-command/).

As well as learning how to use [column](https://man7.org/linux/man-pages/man1/column.1.html) to organize my data for plotting.


