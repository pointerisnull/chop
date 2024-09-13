#ifndef TOKEN_H
#define TOKEN_H

#define SYMBOL_COUNT 32
#define KEYWORD_COUNT 32
#define LITERAL_COUNT 128
#define CONSTANT_COUNT 1024
#define IDENTIFIER_COUNT 1024

static char SYMBOLS[SYMBOL_COUNT] = {
  '\n',
  ',',
  '+',
  '-',
  '*',
  '/',
  '=',
  '%',
  '!',
  '@',
  '&',
  '|',
  '#',
  '<',
  '>',
  '(',
  ')',
  '[',
  ']'
};

static char KEYWORDS[KEYWORD_COUNT][8] = {
  "NULL",
  "VOID",
  "BEGIN",
  "RETURN",
  "IMPORT",
  "IF",
  "ELSE",
  "THEN",
  "FOR",
  "NEXT", //end of for loop
  "WHILE",
  "LOOP", //WEND in basic, end of while
  "8BIT",
  "16BIT",
  "32BIT",
  "64BIT"
};

int *tokenize(char *buffer);

#endif
