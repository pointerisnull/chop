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

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *path);

int main(int argc,  char *argv[]) {

  if (argc > 1) {
    if ((strncmp(argv[1], "-i", 3) == 0))
      printf("Welcome to the CHOP interpreter!\n>\n");
    else if (strncmp(argv[1], "-c", 3) == 0) {
      printf("compiling %s...\n", argv[2]);
    }
    else if (access(argv[1], F_OK | R_OK) == 0) {
      if (argv[1][strlen(argv[1])-1] == '/' && strncmp(argv[1], "/", 2) != 0) 
        argv[1][strlen(argv[1])-1] = '\0'; 
      char *buffer = read_file(argv[1]);
      
      int count = 0;
      char **lines = split(buffer, DELIMITERS, &count);
      //printf("%s\n", buffer);
      /*table_t literal_table = table_create(LITERAL_COUNT, STRING_TYPE);
      table_t constant_table = table_create(CONSTANT_COUNT, INT_TYPE);
      table_t identifier_table = table_create(IDENTIFIER_COUNT, STRING_TYPE);*/
      //debug_print(lines, count);
      int *res = tokenize(lines, count);
      /*table_print(literal_table);
      table_print(constant_table);*/
      free(buffer);
      free_split_string(lines, count);
      /*table_free(&literal_table);
      table_free(&constant_table);
      table_free(&identifier_table);*/
    }
    else
      printf("make sure the file path is correct...\n");
  }
  
  //printf("There is nothing left to do.\n");
  return 0;
}

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
