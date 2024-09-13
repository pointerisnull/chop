#include "config.h"
#include "token.h"
#include "lexer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int *tokenize(char *buffer) {
  //debug_print(&buffer, 1);
  int count = 0;
  char **lines = split(buffer, DELIMITERS, &count);
  //printf("====SPLIT RESULT====\n\n");
  debug_print(lines, count);
  int *res = malloc(count*sizeof(int));
  
  return res;
}
