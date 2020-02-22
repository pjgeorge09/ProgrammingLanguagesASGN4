#include "Givens.h"
#include "Parser.h"

// Static declaration of current position in the lexic array
static int position = 0; 

/* Recursive Descent Parser. Uses Single Symbol Lookahead 
   Arg1 is array of Struct Lexics. Arg2 is the number of lexics in that array.*/
_Bool parser(struct lexics *someLexics, int numberOfLexics){
	// Return true if recursively passes entire grammar AND all tokens are consumed
	if (function(someLexics)){ // Passes all grammar
		if(numberOfLexics==position){ // All tokens consumed
			return(1);
		}
		else{ // Passed Grammar, but not all tokens were consumed
			printf("Not all tokens were consumed! Error!\n");
			printf("File had %d tokens, but returned at token %d.\n", numberOfLexics, position);
			return(0);
		}
	}
	else{ // Failed grammar rule.
		printf("FAILED the EBNF Grammar provided.\n"); 
		return(0);
	}
}

// Method to do single symbol lookahead. Returns the integer token value of next item to parse.
int peek(struct lexics *someLexics){
	return someLexics[position].token;
}

// function --> header body
// Returns true (1) if both pass through all recursion.
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

// header 	--> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
// Method to recursive parse the header
_Bool header(struct lexics *someLexics){
	_Bool headerBool = 1;
	if((headerBool = vartype(someLexics)) != 1){
		printf("Failed in header method when calling header\n"); exit(0);
	}
	if((headerBool = identifier(someLexics)) != 1){
		printf("Failed in header method when calling identifier\n"); exit(0);
	}
	if((headerBool = LP(someLexics)) != 1){
		printf("Failed in header method when calling LP\n"); exit(0);
	}
	if(peek(someLexics) == VARTYPE){
		if((headerBool = argdec(someLexics)) != 1){
			printf("Failed in header method when calling argdec\n"); exit(0);
		}
	}
	if((headerBool = RP(someLexics)) != 1){
		printf("Failed in function method when calling RP\n"); exit(0);
	}
	return headerBool;
}

// Method to consume vartypes  ("int" or "void")
_Bool vartype(struct lexics *someLexics){
	if(someLexics[position].token == VARTYPE){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",VARTYPE,someLexics[position].token,position); exit(0);
	}
}

// Consume Identifiers [a-zA-Z][a-zA-Z0-9]*
_Bool identifier(struct lexics *someLexics){
	if(someLexics[position].token == IDENTIFIER){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",IDENTIFIER,someLexics[position].token,position); exit(0);
	}
}

// Consume "("
_Bool LP(struct lexics *someLexics){
	if(someLexics[position].token == LEFT_PARENTHESIS){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",LEFT_PARENTHESIS,someLexics[position].token,position); exit(0);
	}
}

// Consume ")"
_Bool RP(struct lexics *someLexics){
	if(someLexics[position].token == RIGHT_PARENTHESIS){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",RIGHT_PARENTHESIS,someLexics[position].token,position); exit(0);
	}
}

// arg-decl	--> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER }
// Method to recursive parse arg-decl
_Bool argdec(struct lexics *someLexics){
	_Bool argdecBool = 1;
	if((argdecBool = vartype(someLexics)) != 1){
		printf("Failed in argdec method when calling vartype\n"); exit(0);
	}
	if((argdecBool = identifier(someLexics)) != 1){
		printf("Failed in argdec method when calling identifier\n"); exit(0);
	}
	while(peek(someLexics) == COMMA){
		if((argdecBool = comma(someLexics)) != 1){
			printf("Failed in argdec method when calling comma inside the while loop\n"); exit(0);
		}
		if((argdecBool = vartype(someLexics)) != 1){
			printf("Failed in argdec method when calling vartype\n"); exit(0);
		}
		if((argdecBool = identifier(someLexics)) != 1){
			printf("Failed in argdec method when calling identifier\n"); exit(0);
		}
	}
	return argdecBool;
}

// body --> LEFT_BRACKET [statement-list] RIGHT_BRACKET
// Method to recursive parse body
_Bool body(struct lexics *someLexics){
	_Bool bodyBool = 1;
	if((bodyBool = LB(someLexics)) != 1){
		printf("Failed in body method when calling LB\n"); exit(0);
	}
	int next = peek(someLexics);
	if(next == WHILE_KEYWORD || next == RETURN_KEYWORD || next == IDENTIFIER || next == LEFT_BRACKET){
		if((bodyBool = stmtlist(someLexics)) != 1){
			printf("Failed in body method when calling stmtlist\n"); exit(0);
		}
	}
	if((bodyBool = RB(someLexics)) != 1){
		printf("Failed in function method when calling header\n"); exit(0);
	}
	return bodyBool;
}

// Consume "{"
_Bool LB(struct lexics *someLexics){
	if(someLexics[position].token == LEFT_BRACKET){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",LEFT_BRACKET,someLexics[position].token,position); exit(0);
	}
}

// Consume "}"
_Bool RB(struct lexics *someLexics){
	if(someLexics[position].token == RIGHT_BRACKET){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",RIGHT_BRACKET,someLexics[position].token,position); exit(0);
	}
}

// statement-list 	--> statement {statement}
// Method to recursive parse statement-list
_Bool stmtlist(struct lexics *someLexics){
	_Bool stmtlistBool = 1;
	if((stmtlistBool = stmt(someLexics)) != 1){
		printf("Failed in stmtlist method when calling stmt\n"); exit(0);
	}
	int next = peek(someLexics);
	while(next == WHILE_KEYWORD || next == RETURN_KEYWORD || next == IDENTIFIER || next == LEFT_BRACKET){
		if((stmtlistBool = stmt(someLexics)) != 1){
			printf("Failed in stmtlist method when calling recursive stmt\n"); exit(0);
		}
		next = peek(someLexics);
	}
	return stmtlistBool;	
}

// Consume ','
_Bool comma(struct lexics *someLexics){
	if(someLexics[position].token == COMMA){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",COMMA,someLexics[position].token,position); exit(0);
	}
}

// statement 		--> while-loop | return | assignment | body
// Method to recursive parse statement
_Bool stmt(struct lexics *someLexics){
	_Bool stmtBool = 1;
	if(peek(someLexics) == WHILE_KEYWORD){
		if((stmtBool = _while(someLexics)) != 1){
			printf("Failed in stmt method when calling recursive _while\n"); exit(0);
		}
	}
	else if (peek(someLexics) == RETURN_KEYWORD)	{
		if((stmtBool = _return(someLexics)) != 1){
			printf("Failed in stmt method when calling recursive _return\n"); exit(0);
		}
	}
	else if (peek(someLexics) == IDENTIFIER)	{
		if((stmtBool = assignment(someLexics)) != 1){
			printf("Failed in stmt method when calling recursive asgn\n"); exit(0);
		}
	}
	else if (peek(someLexics) == LEFT_BRACKET)	{
		if((stmtBool = body(someLexics)) != 1){
			printf("Failed in stmt method when calling recursive body\n"); exit(0);
		}
	}
	else{
		printf("Failed in stmt method. Next token was actually a %d %s\n",someLexics[position].token,someLexics[position].lexeme); exit(0);
	}
	return stmtBool;
}

// while-loop 	--> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
// Method to recursive parse while phrase
_Bool _while(struct lexics *someLexics){
	_Bool _whileBool = 1;
	if((_whileBool = whileKeyword(someLexics)) != 1){
		printf("Failed in _while method when calling whileKeyword\n"); exit(0);
	}
	if((_whileBool = LP(someLexics)) != 1){
		printf("Failed in _while method when calling LP\n"); exit(0);
	}
	if((_whileBool = expression(someLexics)) != 1){
		printf("Failed in _while method when calling expression\n"); exit(0);
	}
	if((_whileBool = RP(someLexics)) != 1){
		printf("Failed in _while method when calling RP\n"); exit(0);
	}
	if((_whileBool = stmt(someLexics)) != 1){
		printf("Failed in _while method when calling stmt\n"); exit(0);
	}
	return _whileBool;
}

// return 	--> RETURN_KEYWORD expression EOL
// Method to recursive parse return phrase
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

//assignment --> IDENTIFIER EQUAL expression EOL
// Method to recursive parse assignment
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

// Consume "while"
_Bool whileKeyword(struct lexics *someLexics){
	if(someLexics[position].token == WHILE_KEYWORD){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",WHILE_KEYWORD,someLexics[position].token,position); exit(0);
	}
}

// expression 	--> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
// Method to recursive parse expression
_Bool expression(struct lexics *someLexics){
	_Bool expressionBool = 1;
	int check = peek(someLexics);
	// term {BINOP term}
	if(check != LEFT_PARENTHESIS){
		if((expressionBool = term(someLexics)) != 1){
			printf("Failed in expression method when calling term\n"); exit(0);
		}
		// Conditional BINOP term
		int next = peek(someLexics);
		while(next == BINOP){
			position++; // Increment. We know it's a binop already.
			if((expressionBool = term(someLexics)) != 1){
				printf("Failed in expression method when calling term after a BINOP\n"); exit(0);
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

// Method to consume "return"
_Bool returnKeyword(struct lexics *someLexics){
	if(someLexics[position].token == RETURN_KEYWORD){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",RETURN_KEYWORD,someLexics[position].token,position); exit(0);
	}
}

// Method to consume ';'
_Bool EOLKeyword(struct lexics *someLexics){
	if(someLexics[position].token == EOL){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",EOL,someLexics[position].token,position); exit(0);
	}
}

// Method to consume "="
_Bool equalKeyword(struct lexics *someLexics){
	if(someLexics[position].token == EQUAL){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d, received %d at token number %d\n",EQUAL,someLexics[position].token,position); exit(0);
	}
}

// term 	--> IDENTIFIER | NUMBER 
// Method to consume next term, whether it is ID or Number it gets consumed.
_Bool term(struct lexics *someLexics){
	if(someLexics[position].token == IDENTIFIER || someLexics[position].token == NUMBER){
		position++;
		return 1;
	}
	else{
		printf("Failed. Expected %d or %d, received %d at token number %d\n",IDENTIFIER, NUMBER,someLexics[position].token,position); exit(0);
	}
}



