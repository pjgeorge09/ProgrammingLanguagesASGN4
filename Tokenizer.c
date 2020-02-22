#include "Tokenizer.h"
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
//May need to include <stdio.h>
/* Must use multi-symbol lookahead
   Use fscanf to read from a file (PP10 Slide 24)
*/

//
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
	
	char fileAsString[MY_CHAR_MAX];
	int count = 0;
	// *numLex = 0;

	while(fgets(fileAsString, MY_CHAR_MAX, inf) != NULL){
		int n = 0;
		while(fileAsString[n] != '\0' && fileAsString[n] != '\n'){
			int token;
			int m = 0;
			char holder[MY_CHAR_MAX];
			if(isalpha(fileAsString[n])){
				holder[m] = fileAsString[n];
				n++; m++;
				while(isalpha(fileAsString[n]) || isdigit(fileAsString[n])){
					holder[m] = fileAsString[n];
					n++; m++;
				}
				if (strcmp(holder, "while")==0){
					// printf("Expected WHILE. Received %s\n",holder);
					token = WHILE_KEYWORD;
				}
				else if (strcmp(holder, "return")==0){
					token = RETURN_KEYWORD;
				}
				else if ((strcmp(holder, "int")==0) || (strcmp(holder, "void")==0)){
					token = VARTYPE;
				}
				else{
					token = IDENTIFIER;
				}
			}
			else if(isdigit(fileAsString[n])){
				holder[m] = fileAsString[n];
				n++; m++;
				while(isdigit(fileAsString[n])){
					holder[m] = fileAsString[n];
					n++; m++;
				}
				token = NUMBER;
			}
			else if(isspace(fileAsString[n])){
				n++; m++;
				continue;
			}
			else{
				holder[m] = fileAsString[n];
				// printf("got %s\n", holder);
				switch (fileAsString[n]){
					case '(': token = LEFT_PARENTHESIS; break;
					case ')': token = RIGHT_PARENTHESIS; break;
					case '{': token = LEFT_BRACKET; break;
					case '}': token = RIGHT_BRACKET; break;
					case '=':
						if(fileAsString[n+1] == '='){  //BINOP ==
							n++; m++;
							holder[m] = fileAsString[n];
							token = BINOP;
						}
						else{
							token = EQUAL;
						}
						break;
					case ',': token = COMMA; break;
					case ';': token = EOL; break;
					case '+': token = BINOP; break;
					case '*': token = BINOP; break;
					case '!':
						if(fileAsString[n+1] == '='){  //BINOP ==
							n++; m++;
							holder[m] = fileAsString[n];
							token = BINOP;
						}
						else{
							printf("Expected '!=', but received %c%c\n", fileAsString[n],fileAsString[n+1]);
							exit(0);
						}
						break;
					case '%': token = BINOP; break;
					default: {printf("%s : Did not match any case.\n", holder);}
				}
				n++; m++;
			}
			// At this point I can have Holder holding the lexeme and Token the value and just call it once.
			// ADD NULL TERMINATOR OR WHATEVER
			holder[m] = '\0';
			// struct lexics lexToAdd = makeLexic(token, *holder);

			// printf("Token ID : %d\n", token);
			// printf("Lexeme : %s\n", holder);
			
			// printf("------------->TRUE IS : ");
			printf("%s\n", holder);
			struct lexics *lexToAdd = (struct lexics *) malloc(sizeof(struct lexics));
			for (int x=0; x < m; x++){
				lexToAdd->lexeme[x] = holder[x];
			}
			lexToAdd->token = token;
			aLex[count] = *lexToAdd;
			count++;
			// Need this to zero out the array because it doesn't use local fucking memory i guess
			for (int x=0; x < m; x++){
				holder[x] = '\0';
			}
		}
	}
	*numLex = count;
	return TRUE;
}


// struct lexics makeLexic(int *token, char *heldChars){
// 	struct lexics *toReturn = (struct lexics *) malloc(sizeof(struct lexics));
// 	*toReturn->lexeme = heldChars;
// 	toReturn->token = token;

// 	return *toReturn;
// }
