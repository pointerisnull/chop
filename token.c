#include "config.h"
#include "token.h"
#include "lexer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int *tokenize(char **buffer, int tokc) {
  //debug_print(&buffer, 1);
  //printf("====SPLIT RESULT====\n\n");
  //debug_print(buffer, tokc);
  int *res = malloc(tokc*sizeof(int));
  
  return res;
}
