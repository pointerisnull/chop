#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*utility function*/
int is_delim(char ch, const char *delimiters);
/*given a file buffer, return an array of strings that corrispond with each word*/
char **split(const char *str, const char *delimiters, int *count) {
  size_t size = 64; // Initial size of the result array
  char **result = malloc(size * sizeof(char *));
  if (!result) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  int i = 0, j = 0;
  const char *start = str;
  int ignore_delim = 0; //tag for string literals

  while (*str) {
    
    int delim_res = is_delim(*str, delimiters);
    //regular delimiter case
    if (delim_res == 1 && ignore_delim == 0) {
      if (str > start) { 
        //there is a segment before the delimiter
        int length = str - start;
        result[i] = malloc(length + 1);
        if (!result[i]) {
          perror("Failed to allocate memory");
          exit(EXIT_FAILURE);
        }
        strncpy(result[i], start, length);
        result[i][length] = '\0';
        i++;
      }
      //create separate delimiter string
      result[i] = malloc(2);
      if (!result[i]) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
      }
      result[i][0] = *str;
      result[i][1] = '\0';
      i++;

      //resize if needed
      if (i >= size) {
        size *= 2;
        result = realloc(result, size * sizeof(char *));
        if (!result) {
          perror("Failed to reallocate memory");
          exit(EXIT_FAILURE);
        }
      }

      start = str + 1;
    } else if (delim_res < 0) 
      //if string literal, ignore delimiters untill next "
      ignore_delim = ignore_delim ? 0 : 1; 
    str++;
  }

  //add the last segment of string 
  if (str > start) {
    int length = str - start;
    result[i] = malloc(length + 1);
    if (!result[i]) {
      perror("Failed to allocate memory");
      exit(EXIT_FAILURE);
    }
    strncpy(result[i], start, length);
    result[i][length] = '\0';
    i++;
  }

  //null-terminate the result array
  result[i] = NULL;
  *count = i;

  return result;
}
/*determines if a character is a delimiter or not*/
int is_delim(char ch, const char *delimiters) {
  if(ch == '"' || ch == '#') //case for string literals
    return -1;
  while (*delimiters) {
    if (ch == *delimiters) {
      return 1;
    }
    delimiters++;
  }
  return 0;
}
/*frees the string buffer from memory*/
void free_split_string(char **buffer, int tokc) {
  char **ptr = buffer;
  while (*ptr) {
    free(*ptr);
    ptr++;
  }
  free(buffer); 
}
/*prints the new split string*/
void debug_print(char **buffer, int count) {
  int lc = 1;
  printf("%d.)`", lc);
  for (int i = 0; i < count; i++) {
    if (strcmp(buffer[i], "\n") == 0) {
      lc++;
      printf("\\n`\n%d.)`", lc);
    }
    else if (strcmp(buffer[i], " ") == 0)
      printf("_`");
    else
      printf("%s`", buffer[i]);
  }
  printf("EOF`\n");
}
