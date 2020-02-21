#include "Givens.h"
#include "Parser.h"

static int position;
_Bool parser(struct lexics *someLexics, int numberOfLexics){
	// Recursive Descent Parser, takes in lexics and determine if it is legal
	// in the language defined by the grammar
	// If no syntax errors, return true, otherwise false
	// Utilize single-symbol lookahead
	// "If given a grammatically valid input every token given must be parsed" (wazdis)
	// "Consume 1 token at a time"
	// Create a struct to hold the thing we are currently looking at
	position = 0;
	
	for(int x = 0; x < numberOfLexics; x++){
		struct lexics currentLexic2 = someLexics[x];
		// printf("IN MY PARSER.C FILE : %s  TOKEN %d\n", currentLexic2.lexeme, currentLexic2.token); //print to confirm THIS WORKS RIGHT NOW!
	}
	if ( function(someLexics)){
		printf("Massive Success\n");
	}
	else{
		printf("FAILED the EBNF Grammar provided.");
	}


}

// A method to get the integer token value of the next data
int peek(struct lexics *someLexics){
	struct lexics thisLexic = someLexics[position+1];
	return thisLexic.token;
}

_Bool function(struct lexics *someLexics){
	_Bool functionBool = 1;
	if((functionBool = header(someLexics)) != 1){
		printf("Failed in function method when calling header\n"); exit(0);
	}
	if((functionBool = body(someLexics)) != 1){
		printf("Failed in function method when calling body\n"); exit(0);
	}
	return functionBool;
}

_Bool header(struct lexics *someLexics){
	_Bool headerBool = 1;
	if((headerBool = vartype(someLexics)) != 1){
		printf("Failed in function method when calling header\n"); exit(0);
	}
	if((headerBool = identifier(someLexics)) != 1){
		printf("Failed in function method when calling body\n"); exit(0);
	}
	if((headerBool = LP(someLexics)) != 1){
		printf("Failed in function method when calling body\n"); exit(0);
	}
	// TODO: This needs to be optional depending on the next symbol
	if(peek(someLexics) == VARTYPE){
		printf("Peeked a VARTYPE. This header has an ARGDEC.\n");
		if((headerBool = argDec(someLexics)) != 1){
			printf("Failed in function method when calling body\n"); exit(0);
		}
	}
	
	if((headerBool = RP(someLexics)) != 1){
		printf("Failed in function method when calling body\n"); exit(0);
	}
	return headerBool;
}

_Bool vartype(struct lexics *someLexics){
	if(someLexics->token == VARTYPE){
		return 1;
	}
	else{
		printf("Failed in vartype method. someLexics->token does NOT equal VARTYPE\n"); exit(0);
	}
}

_Bool identifier(struct lexics *someLexics){
	if(someLexics->token == IDENTIFIER){
		return 1;
	}
	else{
		printf("Failed in identifier method. someLexics->token does NOT equal IDENTIFIER\n"); exit(0);
	}
}

_Bool LP(struct lexics *someLexics){
	if(someLexics->token == LEFT_PARENTHESIS){
		return 1;
	}
	else{
		printf("Failed in LP method. someLexics->token does NOT equal LEFT_PARENTHESIS\n"); exit(0);
	}
}

_Bool RP(struct lexics *someLexics){
	if(someLexics->token == RIGHT_PARENTHESIS){
		return 1;
	}
	else{
		printf("Failed in RP method. someLexics->token does NOT equal RIGHT_PARENTHESIS\n"); exit(0);
	}
}



_Bool body(struct lexics *someLexics){

}



