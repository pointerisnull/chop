#include "config.h"
#include "token.h"
#include "lexer.h"
#include "table.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int is_keyword(char *str);
int is_symbol(char *str);
int is_lit(char *str);
int is_int(char *str);
int is_throwaway(char *str);
int classify_token(char *lit);
/*Given an array of strings (and the amount, "tokc"), */
/*return an array of integer codes and update the dictionary*/
int *encode(char **buffer, int *tokc, dictionary_t *dict) {
  
  int *res = malloc(*tokc*sizeof(int));
  /*tokenize each string in the buffer*/
  //printf("String\t\t\t\tCode\n");
  int count = *tokc;
  int sub_delta = 0;
  for (int i = 0; i < count; i++) {
    int class = classify_token(buffer[i]);
    int code = -1;
    if (class == -1) {
      sub_delta++;
    } 
    else if (class >= 0) {  
      code = dict_push(dict, class, buffer[i]);
      res[i-sub_delta] = code;
      //printf("%s \t\t->\t\t%d \n", buffer[i], code);
    }
   
  }
  *tokc -= sub_delta;
  return res;
}

int classify_code(int code, dictionary_t *dict) {
  if (code < dict->keywordmax)
    return KEYWORD_T;
  else if (code < dict->keywordmax+dict->symbolmax)
    return SYMBOL_T;
  else if (code < dict->keywordmax+dict->symbolmax+dict->constantmax)
    return CONSTANT_T;
  else if (code < dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax)
    return LITERAL_T;
  else if (code < dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax+dict->identifiermax)
    return IDENTIFIER_T;
  else return -1;
}

int classify_token(char *lit) {
  int len = strlen(lit);
  //first check if literal is throwaway (whitespace, etc)
  if (is_throwaway(lit)) 
    return -1;
  else if (is_lit(lit))
    return LITERAL_T;
  //check if literal is integer number
  else if (is_int(lit))
    return CONSTANT_T;
  else if (is_keyword(lit))
    return KEYWORD_T;
  else if (is_symbol(lit))
    return SYMBOL_T;
  //if nothing else, it's a new identifier
  else 
    return IDENTIFIER_T;
}

int is_int(char *str) {
  int test = atoi(str);
  if (test != 0) 
    return 1;
  else if (!strncmp(str, "0", 2))
      return 1;
  return 0;
}

int is_keyword(char *str) {
  for (int i = 0; i < KEYWORD_COUNT; i++) {
    if (!strcmp(str, KEYWORDS[i]))
      return 1;
  }
  return 0;
}

int is_symbol(char *str) {
  for (int i = 0; i < SYMBOL_COUNT; i++) {
    if (!strcmp(str, SYMBOLS[i]))
      return 1;
  }
  return 0;
}

int is_lit(char *str) {
  if (str[0] == SYM_STRLIT[0])
    return 1;
  return 0;
}

int is_throwaway(char *str) {
  if (str[0] == '#')
    return 1;
  if (!strncmp(str, " ", 2))
    return 1;
  if (!strncmp(str, "\t", 2))
    return 1;
  if(!strncmp(str, "\r", 2))
    return 1;
  return 0;
}

