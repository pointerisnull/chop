/*******************************\
* COMPILER                      *
*                               *
*   -Brendan Haney 2024         *
\*******************************/
#define VERSION "pre-alpha"

#include "config.h"
#include "token.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *read_file(char *path);

int main(int argc,  char *argv[]) {

  char current_path[MAX_PATH] = {'\0'};
  
  if (argc > 1) {
    if ((strncmp(argv[1], "-i", 3) == 0))
      printf("Welcome to the CHOP interpreter!\n>\n");
    else if (access(argv[1], F_OK | R_OK) == 0) {
      if (argv[1][strlen(argv[1])-1] == '/' && strncmp(argv[1], "/", 2) != 0) 
        argv[1][strlen(argv[1])-1] = '\0'; 
      strncpy(current_path, argv[1], strlen(argv[1]));

      char *buffer = read_file(current_path);
      //printf("%s\n", buffer);
      int *res = tokenize(buffer);
      free(buffer);
    }
    else
      printf("make sure the file path is correct...\n");
    return 0;
  }
  
  printf("There is nothing to do.\n");
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
