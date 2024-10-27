/*******************************\
* CHOP COMPILER                 *
*                               *
*   -Brendan Haney 2024         *
\*******************************/
#define VERSION "a_0.0.1"

#include "config.h"
#include "lexer.h"
#include "token.h"
#include "table.h"
#include "interp.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *path);
void compile_file(char *buffer);

int main(int argc,  char *argv[]) {

  if (argc > 1) {
    /*interpret a file*/
    if ((strncmp(argv[1], "-i", 3) == 0) && access(argv[2], F_OK | R_OK) == 0) {
      printf("interpreting %s...\n", argv[2]);
      char *buffer = read_file(argv[2]);
      dictionary_t dictionary = dict_create();
      interpret_code(buffer, &dictionary);
      free(buffer);
    }
    /*compile a file*/
    else if (access(argv[1], F_OK | R_OK) == 0) {
      /*BEGIN MAIN COMPILER CODE*/
      char *buffer = read_file(argv[1]);
      compile_file(buffer);
      free(buffer);
    }
    else
      printf("make sure the file path is correct...\n");
  } else { /*live interpreter*/
    printf("Welcome to the CHOP interpreter!\n>");
    live_prompt();
  }
  //printf("There is nothing left to do.\n");
  return 0;
}

void compile_file(char *buffer) {
  int count = 0;
  char **lines = split(buffer, DELIMITERS, &count);
  //printf("%s\n", buffer);
  debug_print(lines, count);

  dictionary_t dictionary = dict_create();
     
  int *codes = encode(lines, &count, &dictionary);
  
  for (int i = 0; i < count; i++) {
    printf("%d ", codes[i]);
  }
  printf("\n");

  free(codes);    
  free_split_string(lines, count);
}
/*reads a file from disk and returns it as a string buffer*/
char *read_file(char *path) {
  FILE *file;
  char *buffer;
  size_t file_size;
  size_t result;

  file = fopen(path, "r");
  if (file == NULL) {
    perror("Error opening file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  rewind(file);

  buffer = (char *)malloc(file_size + 1);
  if (buffer == NULL) {
    perror("Memory allocation failed");
    fclose(file);
    return NULL;
  }

  result = fread(buffer, 1, file_size, file);
  if (result != file_size) {
    perror("Reading error");
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[file_size] = '\0';

  fclose(file);
  return buffer;

}
