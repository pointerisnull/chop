#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "table.h"

table_t table_create(int size, int type) {
  table_t ret;
  ret.type = type;
  ret.size = size;
  ret.tokc = 0;
  if (type == STRING_TYPE)
    ret.content_s = malloc(sizeof(char *) * size);
  else 
    ret.content_i = malloc(sizeof(int *) * size);
  return ret;
}

void table_push(table_t *table, void *content) {
  switch (table->type) {
    case INT_TYPE:
      if (table->tokc >= table->size) {
        table->size *= 2;
        table->content_i = realloc(table->content_i, table->size * sizeof(int *));
      }
      table->content_i[table->tokc] = *(int *)content;
      table->tokc ++;

      break;
    case STRING_TYPE:
      if (table->tokc >= table->size) {
        table->size *= 2;
        table->content_s = realloc(table->content_s, table->size * sizeof(char **));
      }
      table->content_s[table->tokc] = (char *)content;
      table->tokc ++;dictionary
      //printf("table content: %s\n", (char *)table->content[table->tokc-1]);
      break;
    default:
      break;
  }
}

void table_free(table_t *table) {
  if (table->type == STRING_TYPE) 
    free(table->content_s);
  else if (table->type == INT_TYPE)
    free(table->content_i);
}

void table_print(table_t table) {
  for (int i = 0; i < table.tokc; i++) {
    if (table.type == STRING_TYPE)
      printf("index %d: %s\n", i, table.content_s[i]);
    else 
      printf("index %d: %d\n", i, table.content_i[i]);
  }
}
