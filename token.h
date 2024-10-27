#ifndef TOKEN_H
#define TOKEN_H

#include "config.h"
#include "table.h"

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
  SYM_RBRACK,
  SYM_EQUIV,
  SYM_GEQUIV,
  SYM_LEQUIV,
  SYM_PP,    
  SYM_MM,
  SYM_PEQUALS,
  SYM_MEQUALS
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

int *encode(char **buffer, int *tokc, dictionary_t *dict);
int classify_code(int code, dictionary_t *dict);

#endif
