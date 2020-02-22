#include "Tokenizer.h"
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* Tokenizer method. Uses Multisymbol Lookahead.
	Arg1 is a pointer to empty array of Struct Lexics to be filled in the tokenizer method
	Arg2 is a pointer to the total number of Struct Lexics in aLex (Arg1)
	Arg3 is a pointer to the file to be read in. Opened in Analyzer.c
	Parses a file. For each token identified, a structure is created, assigning the string
	value of the token to lexeme, and the numeric representation of token.*/
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
	char fileAsString[MY_CHAR_MAX];
	int count = 0;
	// Get one string set at a time, ending in either EOF or EOL
	while(fgets(fileAsString, MY_CHAR_MAX, inf) != NULL){
		int n = 0; // Pointer for current line
		while(fileAsString[n] != '\0' && fileAsString[n] != '\n'){
			int token; // Catch the token to be assigned later
			int m = 0; // Pointer to location is character array of lexeme being built currently
			char holder[MY_CHAR_MAX]; // The lexeme being built currently
			if(isalpha(fileAsString[n])){
				holder[m] = fileAsString[n];
				n++; m++;
				while(isalpha(fileAsString[n]) || isdigit(fileAsString[n])){
					holder[m] = fileAsString[n];
					n++; m++;
				}
				// 12 --> WHILE_KEYWORD --> while
				if (strcmp(holder, "while")==0){
					token = WHILE_KEYWORD;
				}
				// 13 --> RETURN_KEYWORD --> return
				else if (strcmp(holder, "return")==0){
					token = RETURN_KEYWORD;
				}
				// 17 --> VARTYPE --> int | void
				else if ((strcmp(holder, "int")==0) || (strcmp(holder, "void")==0)){
					token = VARTYPE;
				}
				// 55 --> IDENTIFIER --> [a-zA-Z][a-zA-Z0-9]*
				else{
					token = IDENTIFIER;
				}
			}
			// 51 --> NUMBER --> [0-9][0-9]*
			else if(isdigit(fileAsString[n])){
				holder[m] = fileAsString[n];
				n++; m++;
				while(isdigit(fileAsString[n])){
					holder[m] = fileAsString[n];
					n++; m++;
				}
				token = NUMBER;
			}
			// Skip loop on space.
			else if(isspace(fileAsString[n])){
				n++; m++;
				continue;
			}
			// Symbols
			else{
				holder[m] = fileAsString[n];
				switch (fileAsString[n]){
					case '(': token = LEFT_PARENTHESIS; break;
					case ')': token = RIGHT_PARENTHESIS; break;
					case '{': token = LEFT_BRACKET; break;
					case '}': token = RIGHT_BRACKET; break;
					case '=':
						// "==" BINOP
						if(fileAsString[n+1] == '='){ 
							n++; m++;
							holder[m] = fileAsString[n];
							token = BINOP;
						}
						// "=" EQUAL
						else{
							token = EQUAL;
						}
						break;
					case ',': token = COMMA; break;
					case ';': token = EOL; break;
					case '+': token = BINOP; break;
					case '*': token = BINOP; break;
					case '!':
						// "!=" BINOP
						if(fileAsString[n+1] == '='){ 
							n++; m++;
							holder[m] = fileAsString[n];
							token = BINOP;
						}
						// Error in any other case.
						else{
							printf("Expected '!=', but received %c%c\n", fileAsString[n],fileAsString[n+1]);
							return(0);
						}
						break;
					case '%': token = BINOP; break;
					default: {printf("%s : Did not match any case.\n", holder);}
				}
				n++; m++;
			}
			// Add string terminator
			holder[m] = '\0';
			// Create the structure to be added to the Struct Lexic array
			struct lexics *lexToAdd = (struct lexics *) malloc(sizeof(struct lexics));
			// Set each character individually using the holder created.
			for (int x=0; x < m; x++){
				lexToAdd->lexeme[x] = holder[x];
			}
			// Set the token of this created lex to the token caught above
			lexToAdd->token = token;
			// Set the Struct Lexics array at this point to this structure created
			aLex[count] = *lexToAdd;
			// Increment the count of structures added to the Struct Lexics array
			count++;
			// Manually set all values in holder to '\0' because C is ridiculous
			for (int x=0; x < m; x++){
				holder[x] = '\0';
			}
		}
	}
	// After everything, set pointer to the number of lexics in aLex to the number we tokenized.
	*numLex = count;
	return TRUE;
}