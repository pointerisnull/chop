#include <stdlib.h>
#include <stdio.h>
#include "cono.h"
#include "token.h"
#include "table.h"
#include "config.h"

/*KEYWORDS -> THEN SYMBOLS*/
char *getop_str(int **ctable, int co, int no) {
  int code = ctable[co][no];
  switch(code) {
    case ERR:
      return "ERR";
      break;
    case NOOP:
      return "NOOP";
      break;
    case NEWLN:
      return "NEWLN";
      break;
    case STARTDEF:
      return "STARTDEF";
      break;
    case ENDDEF:
      return "ENDDEF";
      break;
    case INPUT:
      return "INPUT";
      break;
    case PRINT:
      return "PRINT";
      break;
    case FUNCDEF:
      return "FUNCDEF";
      break;
    case PARAM:
      return "PARAM";
      break;
    case ENDPAREN:
      return "ENDPAREN";
      break;
    case STARTPROG:
      return "STARTPROG";
      break;
    case RETURN:
      return "RETURN";
      break;
  }
  return "ERR";
}

void cono_combo(int **ctable, dictionary_t *dict) {
  int size = dict->keywordmax + dict->symbolmax;

  for (int i = 0; i < size; i++) {
    /*\n -> anything = NOOP*/
    ctable[dict_push(dict, SYMBOL_T, SYM_NEWLINE)][i] = NOOP; 
    /*RETURN -> anything = RETURN*/
    ctable[dict_push(dict, KEYWORD_T, KEYWORD_RETURN)][i] = RETURN; 
    /*PRINT -> anything = PRINT*/
    ctable[dict_push(dict, KEYWORD_T, KEYWORD_PRINT)][i] = PRINT; 
  }
  /*datatype -> equals = STARTDEF*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_EQUALS)] = STARTDEF; 
  /*datatype -> \n = ENDDEF*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_NEWLINE)] = ENDDEF; 
  /*datatype -> , = ENDDEF*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_COMMA)] = ENDDEF; 
  /*datatype -> ) = ENDDEF*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_RPAREN)] = ENDDEF; 
  /*equals -> \n = ENDDEF*/
  ctable[dict_push(dict, SYMBOL_T, SYM_EQUALS)][dict_push(dict, SYMBOL_T, SYM_NEWLINE)] = ENDDEF; 
  /*datatype -> ( = FUNCDEF*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_LPAREN)] = FUNCDEF; 
  /*( -> , = PARAM*/
  ctable[dict_push(dict, SYMBOL_T, SYM_LPAREN)][dict_push(dict, SYMBOL_T, SYM_COMMA)] = PARAM; 
  /*( -> datatype = PARAM (definition)*/
  ctable[dict_push(dict, SYMBOL_T, SYM_LPAREN)][dict_push(dict, KEYWORD_T, KEYWORD_i8)] = PARAM; 
  /*, -> datatype = PARAM*/
  ctable[dict_push(dict, SYMBOL_T, SYM_COMMA)][dict_push(dict, KEYWORD_T, KEYWORD_i8)] = PARAM; 
  /*, -> ) = PARAMETER (last)*/
  ctable[dict_push(dict, SYMBOL_T, SYM_COMMA)][dict_push(dict, SYMBOL_T, SYM_RPAREN)] = PARAM; 
  /*datatype -> ) = ENDPAREN*/
  //ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_RPAREN)] = ENDPAREN; 
  /*( -> ) = ONE PARAMETER*/
  ctable[dict_push(dict, SYMBOL_T, SYM_LPAREN)][dict_push(dict, SYMBOL_T, SYM_RPAREN)] = PARAM; 
  /*) -> \n = ENDPAREN*/
  ctable[dict_push(dict, SYMBOL_T, SYM_RPAREN)][dict_push(dict, SYMBOL_T, SYM_NEWLINE)] = ENDPAREN; 
  /*BEGIN -> \n = STARTPROG*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_BEGIN)][dict_push(dict, SYMBOL_T, SYM_NEWLINE)] = STARTPROG; 
}

int **init_cono(dictionary_t *dict) {
  int **ctable;
  int size = dict->keywordmax + dict->symbolmax;
  ctable = malloc(sizeof(int *)*size);
  for (int i = 0; i < size; i++)
    ctable[i] = malloc(sizeof(int)*size);
  /*initialize all vales to ERROR*/
  for (int i = 0; i < size; i++) 
    for (int j = 0; j < size; j++) 
      ctable[i][j] = ERR;

  cono_combo(ctable, dict);
  

  return ctable;
}

void print_cono(int **ctable, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (ctable[i][j] == -1)
        printf("_ ");
      else if (ctable[i][j] < 10)
        printf("%d ", ctable[i][j]);
      else
        printf("%d", ctable[i][j]);
    }
   printf("\n");
  }
}
