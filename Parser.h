#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"

_Bool parser(struct lexics *someLexics, int numberOfLexics);

// Methods Used. Described in the .c file as to document process.
//  arg *someLexics is the array at lexics for all methods.
int peek(struct lexics *someLexics);
_Bool function(struct lexics *someLexics);
_Bool header(struct lexics *someLexics);
_Bool vartype(struct lexics *someLexics);
_Bool identifier(struct lexics *someLexics);
_Bool LP(struct lexics *someLexics);
_Bool RP(struct lexics *someLexics);
_Bool argdec(struct lexics *someLexics);
_Bool body(struct lexics *someLexics);
_Bool LB(struct lexics *someLexics);
_Bool RB(struct lexics *someLexics);
_Bool stmtlist(struct lexics *someLexics);
_Bool comma(struct lexics *someLexics);
_Bool stmt(struct lexics *someLexics);
_Bool _while(struct lexics *someLexics);
_Bool _return(struct lexics *someLexics);
_Bool assignment(struct lexics *someLexics);
_Bool whileKeyword(struct lexics *someLexics);
_Bool expression(struct lexics *someLexics);
_Bool returnKeyword(struct lexics *someLexics);
_Bool EOLKeyword(struct lexics *someLexics);
_Bool equalKeyword(struct lexics *someLexics);
_Bool term(struct lexics *someLexics);

#endif
