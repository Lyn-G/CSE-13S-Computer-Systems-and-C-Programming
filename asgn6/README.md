### Description of the Assignment

Our program will read in a list of words that are considered badspeak. Then we will read in oldspeak and newspeak pairs. We will parse the words with our own module and check to see if it has been added to the Bloom filter that we must create ourselves. If it is likely that the word has been added, then we need to insert this badspeak word into a list accordingly. We will print out different warnings for what transgressions are found. 


### How I Built It

Words will be read in, and it is our program's job to filter out the words that are deemed bad.
We store bad words in our hash table and Bloom filter.
Our Bloom filter is constructed using bit vectors, while our hash table is created using linked lists. Our linked list is also constructed with nodes.
We use these structures to help us with parsind through words and inserting words into our respective linked lists.
We are also able to track and print out statistics for many different sections.


### How to Run It

1. Compile the assignment files.
2. Run banhammer along with any of the option commands (if an invalid option is put, then banhammer will print out the help message):
    -h prints out the program usage.
    -t size specifies that the hash table will have size entries (the default will be 10000).
    -f size specifies that the Bloom filter will have size entries (the default will be 219 ).
    -m will enable the move-to-front rule.
    -s will enable the printing of statistics. 
	
	
### Bugs

I understand that my code does not function as intended. Whenever my code is ran through the terminal, it is accessing memory that it shouldn't, which is why it outputs special characters. This causes it to always output the mixspeak message. 

Previously, my code would also error because it would try to free a pointer that can't be freed.

Some statistics do not properly represent or change when enabling them.


### Cite Sources

Resources that I used:

I used this [link](https://www.geeksforgeeks.org/arrow-operator-in-c-c-with-examples/#) to help me understand structures and using the arrow operator.

I used this [link](https://www.geeksforgeeks.org/strdup-strdndup-functions-c/) to help me conceptually understand strdup(), which, like the assignment told us to do, I did not use.

I used this [link](https://www.geeksforgeeks.org/tolower-function-in-c/) to help me understand tolower().

I used this [link](https://www.geeksforgeeks.org/isalnum-function-c-language/) to help me understand isalnum().

I used this [link](https://www.scaler.com/topics/c/assignment-operators-in-c/) to better my coding and learned that there were bitwise assignment operators.
