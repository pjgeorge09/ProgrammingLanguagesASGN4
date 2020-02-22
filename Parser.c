#include "Givens.h"
#include "Parser.h"

static int position = 0;
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
	if (function(someLexics)){
		printf("Massive Success\n");
	}
	else{
		printf("FAILED the EBNF Grammar provided.");
	}


}

// A method to get the integer token value of the next data
int peek(struct lexics *someLexics){
	return someLexics[position].token;
}

_Bool function(struct lexics *someLexics){
	// return (header(someLexics) && body(someLexics));
	_Bool functionBool = 1;
	if((functionBool = header(someLexics)) != 1){
		printf("Failed in function method when calling header\n"); exit(0);
	}
	if((functionBool = body(someLexics)) != 1){
		printf("Failed in function method when calling body\n"); exit(0);
	}
	return functionBool;
}

// 
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
		// printf("Peeked a VARTYPE. This header has an ARGDEC.\n");
		if((headerBool = argdec(someLexics)) != 1){
			printf("Failed in function method when calling body\n"); exit(0);
		}
	}
	
	if((headerBool = RP(someLexics)) != 1){
		printf("Failed in function method when calling body\n"); exit(0);
	}
	return headerBool;
}

// checked
_Bool vartype(struct lexics *someLexics){
	if(someLexics[position].token == VARTYPE){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in vartype method. someLexics[position].token does NOT equal VARTYPE\n"); exit(0);
	}
}

_Bool identifier(struct lexics *someLexics){
	if(someLexics[position].token == IDENTIFIER){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in indentifier method. someLexics[position].token does NOT equal IDENTIFIER\n"); exit(0);
	}
}

_Bool LP(struct lexics *someLexics){
	if(someLexics[position].token == LEFT_PARENTHESIS){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in LP method. someLexics[position].token does NOT equal LEFT_PARENTHESIS\n"); exit(0);
	}
}

_Bool RP(struct lexics *someLexics){
	if(someLexics[position].token == RIGHT_PARENTHESIS){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in RP method. someLexics[position].token does NOT equal RIGHT_PARENTHESIS\n"); exit(0);
	}
}

// Been checked, should be fine.
_Bool argdec(struct lexics *someLexics){
	_Bool argdecBool = 1;
	if((argdecBool = vartype(someLexics)) != 1){
		printf("Failed in argdec method when calling vartype\n"); exit(0);
	}
	if((argdecBool = identifier(someLexics)) != 1){
		printf("Failed in argdec method when calling identifier\n"); exit(0);
	}
	int next = peek(someLexics);
	// TODO: This needs to be optional depending on the next symbol
	while(next == COMMA){
		if((argdecBool = comma(someLexics)) != 1){
			printf("Failed in argdec method when calling comma inside the while loop\n"); exit(0);
		}
		if((argdecBool = vartype(someLexics)) != 1){
			printf("Failed in argdec method when calling vartype\n"); exit(0);
		}
		if((argdecBool = identifier(someLexics)) != 1){
			printf("Failed in argdec method when calling identifier\n"); exit(0);
		}
		next = peek(someLexics);	
	}
	return argdecBool;
}

_Bool body(struct lexics *someLexics){
	_Bool bodyBool = 1;

	if((bodyBool = LB(someLexics)) != 1){
		printf("Failed in body method when calling LB\n"); exit(0);
	}
	// On the condition that the next keyword is not RIGHT_BRACKET
	int next = peek(someLexics);
	if(next == WHILE_KEYWORD || next == RETURN_KEYWORD || next == IDENTIFIER || next == LEFT_BRACKET){
		printf("Peeked a %d. This header has an 'STMT-LIST'.\n", next);
		// Recursively go into statement list here
		if((bodyBool = stmtlist(someLexics)) != 1){
			printf("Failed in body method when calling stmtlist\n"); exit(0);
		}
	}
	if((bodyBool = RB(someLexics)) != 1){
		printf("Failed in function method when calling header\n"); exit(0);
	}
	// Should only return if it got 1 from everything
	return bodyBool;
}


_Bool LB(struct lexics *someLexics){
	if(someLexics[position].token == LEFT_BRACKET){
		position++;
		return 1;
	}
	else{
		printf("Failed in LB method. someLexics[position].token does NOT equal LEFT_BRACKET\n"); exit(0);
	}
}

_Bool RB(struct lexics *someLexics){
	if(someLexics[position].token == RIGHT_BRACKET){
		position++;
		return 1;
	}
	else{
		printf("Failed in RB method. someLexics[position].token does NOT equal RIGHT_BRACKET\n"); exit(0);
	}
}

// TODO
_Bool stmtlist(struct lexics *someLexics){
	_Bool stmtlistBool = 1;

	if((stmtlistBool = stmt(someLexics)) != 1){
		printf("Failed in stmtlist method when calling stmt\n"); exit(0);
	}

	int next = peek(someLexics);
	while(next == WHILE_KEYWORD || next == RETURN_KEYWORD || next == IDENTIFIER || next == LEFT_BRACKET){
		printf("Peeked a %d. This header has an 'STMT-LIST'.\n", next);
		// Recursively go into statement list here
		if((stmtlistBool = stmt(someLexics)) != 1){
			printf("Failed in stmtlist method when calling recursive stmt\n"); exit(0);
		}
		next = peek(someLexics);
	}
	return stmtlistBool;	
}

_Bool comma(struct lexics *someLexics){
	if(someLexics[position].token == COMMA){
		position++;
		return 1;
	}
	else{
		printf("Failed in comma method. someLexics[position].token does NOT equal COMMA\n"); exit(0);
	}
}

_Bool stmt(struct lexics *someLexics){
	_Bool stmtBool = 1;
	int next = peek(someLexics);
	// Cases it can be are while_keyword, return_keyword, identifier, LB if goes to body but no STMTLIST, 
	printf("CRITICAL TESTING : AT POSITION %d, %s\n", someLexics[position].token, someLexics[position].lexeme);
	if(next == WHILE_KEYWORD){
		if((stmtBool = _while(someLexics)) != 1){
			printf("Failed in stmt method when calling recursive _while\n"); exit(0);
		}
	}
	else if (next == RETURN_KEYWORD)	{
		if((stmtBool = _return(someLexics)) != 1){
			printf("Failed in stmt method when calling recursive _return\n"); exit(0);
		}
	}
	else if (next == IDENTIFIER)	{
		if((stmtBool = assignment(someLexics)) != 1){
			printf("Failed in stmt method when calling recursive asgn\n"); exit(0);
		}
	}
	else if (next == LEFT_BRACKET)	{
		if((stmtBool = body(someLexics)) != 1){
			printf("Failed in stmt method when calling recursive body\n"); exit(0);
		}
	}
	else{
		printf("Failed in stmt method. Next token was actually a %d %s\n",someLexics[position-1].token,someLexics[position-1].lexeme);
		printf("Failed in stmt method. Next token was actually a %d %s\n",someLexics[position].token,someLexics[position].lexeme);
		printf("Failed in stmt method. Next token was actually a %d %s\n",someLexics[position+1].token,someLexics[position+1].lexeme);
		exit(0);
	}
	return stmtBool;
}

// while-loop 		--> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
_Bool _while(struct lexics *someLexics){
	_Bool _whileBool = 1;
	int next = peek(someLexics);
	
	if((_whileBool = whileKeyword(someLexics)) != 1){
		printf("Failed in _while method when calling whileKeyword\n"); exit(0);
	}
	if((_whileBool = LP(someLexics)) != 1){
		printf("Failed in _while method when calling LP\n"); exit(0);
	}
	// Its likely here
	if((_whileBool = expression(someLexics)) != 1){
		printf("Failed in _while method when calling expression\n"); exit(0);
	}
	if((_whileBool = RP(someLexics)) != 1){
		printf("Failed in _while method when calling RP\n"); exit(0);
	}
	// Or here
	if((_whileBool = stmt(someLexics)) != 1){
		printf("Failed in _while method when calling stmt\n"); exit(0);
	}
	return _whileBool;
}

_Bool _return(struct lexics *someLexics){
	_Bool _returnBool = 1;
	if((_returnBool = returnKeyword(someLexics)) != 1){
		printf("Failed in _return method when calling returnKeyword\n"); exit(0);
	}
	if((_returnBool = expression(someLexics)) != 1){
		printf("Failed in _return method when calling expression\n"); exit(0);
	}
	if((_returnBool = EOLKeyword(someLexics)) != 1){
		printf("Failed in _return method when calling EOLKeyword\n"); exit(0);
	}
	return _returnBool;
}

//assignment 		--> IDENTIFIER EQUAL expression EOL

_Bool assignment(struct lexics *someLexics){
	_Bool assignmentBool = 1;
	if((assignmentBool = identifier(someLexics)) != 1){
		printf("Failed in assignment method when calling identifier\n"); exit(0);
	}
	if((assignmentBool = equalKeyword(someLexics)) != 1){
		printf("Failed in assignment method when calling equalKeyword\n"); exit(0);
	}
	if((assignmentBool = expression(someLexics)) != 1){
		printf("Failed in assignment method when calling expression\n"); exit(0);
	}
	if((assignmentBool = EOLKeyword(someLexics)) != 1){
		printf("Failed in assignment method when calling EOLKeyword\n"); exit(0);
	}
	return assignmentBool;
}

_Bool whileKeyword(struct lexics *someLexics){
	if(someLexics[position].token == WHILE_KEYWORD){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in whileKeyword method. someLexics[position].token does NOT equal WHILE_KEYWORD\n"); exit(0);
	}
}

//expression 		--> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
// Pretty sure this is my issue
_Bool expression(struct lexics *someLexics){
	_Bool expressionBool = 1;
	printf("Expression checking. currently at %d %s\n",someLexics[position].token, someLexics[position].lexeme);
	// int next = peek(someLexics);
	// if(next == IDENTIFIER || next == NUMBER){
	// 	if((expressionBool = term(someLexics)) != 1){
	// 			printf("Failed in expression method when calling term\n"); exit(0);
	// 	}
	// 	next = peek(someLexics);
	// 	while(next == BINOP){

	// 	}
	// }


	int check = peek(someLexics);
	// term {BINOP term}
	if(check != LEFT_PARENTHESIS){
		if((expressionBool = term(someLexics)) != 1){
			printf("Failed in expression method when calling term\n"); exit(0);
		}
		// Conditional BINOP term
		// I think the error is right here
		int next = peek(someLexics);
		while(next == BINOP){
			position++; // Increment. We know it's a binop already.
			if((expressionBool = term(someLexics)) != 1){
				printf("Failed in expression method when calling term\n"); exit(0);
			}
			next = peek(someLexics);
		}
	}
	// ( expression )
	else{
		if((expressionBool = LP(someLexics)) != 1){
			printf("Failed in expression method when calling LP\n"); exit(0);
		}
		if((expressionBool = expression(someLexics)) != 1){
			printf("Failed in expression method when calling expression\n"); exit(0);
		}
		if((expressionBool = RP(someLexics)) != 1){
			printf("Failed in expression method when calling RP\n"); exit(0);
		}

	}
	return expressionBool;
}


_Bool binop(struct lexics *someLexics){
	if(someLexics[position].token == BINOP){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in equalKeyword method. someLexics[position].token does NOT equal BINOP\n"); exit(0);
	}
}


_Bool returnKeyword(struct lexics *someLexics){
	if(someLexics[position].token == RETURN_KEYWORD){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in returnKeyword method. someLexics[position].token does NOT equal RETURN_KEYWORD\n"); exit(0);
	}
}

_Bool EOLKeyword(struct lexics *someLexics){
	if(someLexics[position].token == EOL){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in EOLKeyword method. someLexics[position].token does NOT equal EOL\n"); exit(0);
	}
}

_Bool equalKeyword(struct lexics *someLexics){
	if(someLexics[position].token == EQUAL){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Failed in equalKeyword method. someLexics[position].token does NOT equal EQUAL\n"); exit(0);
	}
}

_Bool term(struct lexics *someLexics){
	if(someLexics[position].token == IDENTIFIER || someLexics[position].token == NUMBER){
		position++;
		return 1;
	}
	else{
		printf("Actual %s\n", someLexics[position].lexeme);
		printf("Lexeme number %d\n", position);
		printf("Failed in term method. someLexics[position].token does NOT equal IDENTIFIER nor NUMBER\n"); exit(0);
	}
}



