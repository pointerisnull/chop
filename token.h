#ifndef TOKEN_H
#define TOKEN_H

#include "config.h"

static char SYMBOLS[SYMBOL_COUNT][3] = {
  SYM_NEWLINE,
  SYM_COMMA,  
  SYM_PLUS,   
  SYM_MINUS,  
  SYM_STAR,   
  SYM_FSLASH, 
  SYM_BSLASH,
  SYM_EQUALS, 
  SYM_MODULO, 
  SYM_NOT,    
  SYM_ADDR,   
  SYM_PIPE,   
  SYM_COMMENT,
  SYM_STRLIT, 
  SYM_LESS,    
  SYM_GREATER, 
  SYM_LPAREN,  
  SYM_RPAREN,  
  SYM_LBRACK,  
  SYM_RBRACK  
};

static char KEYWORDS[KEYWORD_COUNT][8] = {
  KEYWORD_NULL, 
  KEYWORD_VOID,
  KEYWORD_BEGIN,
  KEYWORD_RETURN,
  KEYWORD_IMPORT,
  KEYWORD_IF, 
  KEYWORD_ELSE, 
  KEYWORD_THEN,  
  KEYWORD_FOR, 
  KEYWORD_NEXT,
  KEYWORD_WHILE,
  KEYWORD_LOOP,  
  KEYWORD_PRINT,  
  KEYWORD_i8,  
  KEYWORD_i16,  
  KEYWORD_i32,
  KEYWORD_i64
};

int *tokenize(char **buffer, int tokc);

#endif
