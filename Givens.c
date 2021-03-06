#include "Givens.h"

_Bool validNumber(char* aLexeme){
	regex_t numberRegex;
	// Regex starts with a number, any list of numbers. ONLY number.
	regcomp(&numberRegex, "^[0-9][0-9]*$", REG_EXTENDED);
	return !regexec(&numberRegex, aLexeme, 0, 0, 0);	
}

_Bool validIdentifier(char * aLexeme){
	regex_t identifierRegex;
	// Regex starts with any alphabet char, ends with alphanumeric. No breaks for non-alphanumeric tokens
	regcomp(&identifierRegex, "^[a-zA-Z][a-zA-Z0-9]*$", REG_EXTENDED);
	return !regexec(&identifierRegex, aLexeme, 0, 0, 0);
}
