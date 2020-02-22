#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Givens.h"
#include "Analyzer.h"

/* Tokenizer method. Uses Multisymbol Lookahead.
	Arg1 is a pointer to empty array of Struct Lexics to be filled in the tokenizer method
	Arg2 is a pointer to the total number of Struct Lexics in aLex (Arg1)
	Arg3 is a pointer to the file to be read in. Opened in Analyzer.c
	Parses a file. For each token identified, a structure is created, assigning the string
	value of the token to lexeme, and the numeric representation of token.*/
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

#endif
