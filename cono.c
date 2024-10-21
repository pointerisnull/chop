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
  }
  /*datatype -> equals = STARTDEF*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_EQUALS)] = STARTDEF; 
  /*datatype -> \n = ENDDEF*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_EQUALS)] = ENDDEF; 
  /*equals -> \n = ENDDEF*/
  ctable[dict_push(dict, SYMBOL_T, SYM_EQUALS)][dict_push(dict, SYMBOL_T, SYM_NEWLINE)] = ENDDEF; 
  /*datatype -> ( = FUNCDEF*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_i8)][dict_push(dict, SYMBOL_T, SYM_LPAREN)] = ENDDEF; 
  /*( -> , = PARAM*/
  ctable[dict_push(dict, SYMBOL_T, SYM_LPAREN)][dict_push(dict, SYMBOL_T, SYM_COMMA)] = PARAM; 
  /*, -> , = PARAM*/
  ctable[dict_push(dict, SYMBOL_T, SYM_COMMA)][dict_push(dict, SYMBOL_T, SYM_COMMA)] = PARAM; 
  /*, -> ) = ENDPAREN*/
  ctable[dict_push(dict, SYMBOL_T, SYM_COMMA)][dict_push(dict, SYMBOL_T, SYM_RPAREN)] = ENDPAREN; 
  /*( -> ) = ENDPAREN*/
  ctable[dict_push(dict, SYMBOL_T, SYM_LPAREN)][dict_push(dict, SYMBOL_T, SYM_RPAREN)] = ENDPAREN; 
  /*) -> \n = NOOP*/
  ctable[dict_push(dict, SYMBOL_T, SYM_RPAREN)][dict_push(dict, SYMBOL_T, SYM_NEWLINE)] = NOOP; 
  /*BEGIN -> \n = STARTPROG*/
  ctable[dict_push(dict, KEYWORD_T, KEYWORD_BEGIN)][dict_push(dict, SYMBOL_T, SYM_NEWLINE)] = STARTPROG; 
}

void init_cono(int **ctable, dictionary_t *dict) {
  int size = dict->keywordmax + dict->symbolmax;
  ctable = malloc(sizeof(int *)*size);
  for (int i = 0; i < size; i++)
    ctable[i] = malloc(sizeof(int)*size);
  /*initialize all vales to ERROR*/
  for (int i = 0; i < size; i++) 
    for (int j = 0; j < size; j++) 
      ctable[i][j] = ERR;

  cono_combo(ctable, dict);
  
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
