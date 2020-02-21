#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Givens.h"
#include "Analyzer.h"

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

struct lexics makeLexic(int *token, char *heldChars);

#endif
