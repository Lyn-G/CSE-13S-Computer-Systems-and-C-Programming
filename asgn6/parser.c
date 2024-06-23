#include "parser.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> 
#include <stdio.h>
#include <ctype.h>

#define MAX_PARSER_LINE_LENGTH 1000

struct Parser {
FILE *f;
char current_line[MAX_PARSER_LINE_LENGTH + 1];
uint32_t line_offset;
};

// constructor for the parser
Parser *parser_create(FILE *f) {
	Parser *p = (Parser *) malloc(sizeof(Parser));

	if (p != NULL) {
		p->line_offset = 0;
		p->f = f;
		
	}
	return p;
}

// pointer to the parser should be set to NULL
void parser_delete(Parser **p) {
	if (*p) {

		free (*p);
		*p = NULL;
	}

}

// it will find the next valid word in the buffer within the parser and store it in the buffer passed in
// if the next word was successfully parsed, return true and copy the word into *word (including a "\0")
// if there are no more words left, the function returns false and *word is undefined
// convert all uppercase letters to lowercase
// use tolower() and isalnum()
bool next_word(Parser *p, char *word){
	if (p) {
		if (p->current_line[0] == '\0' || p->current_line[p->line_offset] == '\0' || !(p->current_line[p->line_offset])) {
			for (int i = 0; i < MAX_PARSER_LINE_LENGTH + 1; i ++) {
				p->current_line[i] = 0;
				
			} // end of for-loop
			
			// get file contents and check if it's false
			if (!(fgets(p->current_line, MAX_PARSER_LINE_LENGTH + 1, p->f))) {
				return false; // we've reached the end of the file
			} // end of if-statement
			
			p->line_offset = 0;
			
		} // end of if-statement
		
		// copy words into buffer
		int k = 0;
		
		for ( k = 0; k < MAX_PARSER_LINE_LENGTH + 1; k++){
			 // index variable
			
			//printf("%c\n",p->current_line[p->line_offset]);
			if (!isalnum(p->current_line[p->line_offset]) 
			
			// ASCII numbers
			&& ((p->current_line[p->line_offset] != 45) && (p->current_line[p->line_offset] != 39))) {
				p->line_offset ++;
				
				// break out of for-loop if new word
				break;
			}
			
			word[k] = tolower(p->current_line[p->line_offset]);
			
			
			/*printf("%c\n", p->current_line[p->line_offset]); 
			printf("word characters %c \n", word[k]);
			printf("%s : word \n", word);*/
			

			p->line_offset ++;
		
		} // end of for-loop
		word[k] = '\0';
		// printf("%s : word1 \n", word);
	}
	return true;
	
}


/*int main () {
	Parser *p;
	FILE *badspeak = fopen("hello.txt", "r");
	char word[MAX_PARSER_LINE_LENGTH];
	char nword[MAX_PARSER_LINE_LENGTH];
	
	p = parser_create( badspeak);

	while (next_word(p, word)) {
	//	puts("makes it inside");
		printf("bf %s\n", word);
		next_word(p, nword);
		printf("ht %s->%s\n", word, nword);
	
	}
	return 0;
}
*/
