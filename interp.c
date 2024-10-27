#include "config.h"
#include "interp.h"
#include "lexer.h"
#include "token.h"
#include "table.h"
#include "cono.h"

#include <stdio.h>
#include <stdlib.h>

int march_op(dictionary_t *dict, int *codes, int size, int current) {
  //int next = current;
  for (int i = current+1; i < size; i++) {
    int class = classify_code(codes[i], dict);
    //printf("class: %d\n", class);
    if (class == KEYWORD_T || class == SYMBOL_T)
      return i;
  }
  return size;
}

int handle_op(dictionary_t *dict, int *codes, int op) {
  switch (op) {
    case RETURN:
      return EXIT;
  }
  return ERR;
}

int interpret_code(char *buffer, dictionary_t *dict) {
  int count = 0;
  char **tokens = split(buffer, DELIMITERS, &count);
  int *codes = encode(tokens, &count, dict);
  int **cono = init_cono(dict);
  char *op = getop_str(cono, codes[0] , codes[2]);
  
  //print_cono(cono, 64);
  for (int i = 0; i < count; i++) {
    printf("%d ", codes[i]);
  }
  printf("\n");
  
  //print the opporations
  for (int i = 0; i < count; i++) {
    int co = i;
    int no = march_op(dict, codes, count, i);
    printf("co %d no %d ", co, no);
    char *op = getop_str(cono, codes[i], codes[no]);
    printf(": %s\n", op);
    i = no-1;
  }
  //do the operations
  for (int i = 0; i < count; i++) {
    int co = i;
    int no = march_op(dict, codes, count, i);
    int handle = handle_op(dict, codes, cono[co][no]);
    if (handle == EXIT) return EXIT;
    //printf("co %d no %d ", co, no);
    //char *op = getop_str(cono, codes[i], codes[no]);
    //printf("%s: ", op);
    i = no-1;
  }
  printf("\n>");
  free(codes);
  free_split_string(tokens, count);
  return CONTINUE;
}

void live_prompt() {
  dictionary_t dict = dict_create();
  char *line;
  size_t len = 0;
  
  ssize_t read;
  int status = 0;
  while (status != EXIT) {
    // Read a line from the console
    read = getline(&line, &len, stdin);
    if (read != -1) {
      // Output the line that was read
      printf("You entered: %s", line);
      status = interpret_code(line, &dict);
    } else {
      // Handle error in reading
      printf("Error reading input.\n");
    }
  }
  free(line);
}
