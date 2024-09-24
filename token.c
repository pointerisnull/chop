#include "config.h"
#include "token.h"
#include "lexer.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int is_integer(char *lit, int len) {
  int res = atoi(lit);
  if (atoi != 0)
    return 1;
  return 0;
}

int classify_literal(char *lit) {
  int len = strlen(lit);
  //first check if literal is throwaway (whitespace, etc)
  if (strcmp(lit, " ")) 
    return 0;
  //check if literal is integer number
  if (is_integer(lit, len))
    return 1;

  return 0;
}

int *tokenize(char **buffer, int tokc) {
  
  int *res = malloc(tokc*sizeof(int));
  /*tokenize each string in the buffer*/
  for (int i = 0; i < tokc; i++) {
    int new_tag = 1;
    for (int j = 0; j < KEYWORD_COUNT+SYMBOL_COUNT+LITERAL_COUNT; j++) {
      if (!strcmp(buffer[i], KEYWORDS[j]) && j < KEYWORD_COUNT) {
        //printf("Keyword %s is %d\n", buffer[i], j);
        new_tag = 0;
        break;
      }
      else if (!strcmp(buffer[i], SYMBOLS[j-KEYWORD_COUNT]) && j < KEYWORD_COUNT+SYMBOL_COUNT) {
        //printf("Symbol %s at i %d is index %d\n", buffer[i], i, j-KEYWORD_COUNT);
        new_tag = 0;
        break;
      }
    }
    if (new_tag) {
      int cls = classify_literal(buffer[i]);
  }
  
  return res;
}
