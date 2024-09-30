#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "config.h"

int to_int(char *str);

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
      int num = to_int((char*)content);

      if (table->tokc >= table->size) {
        table->size *= 2;
        table->content_i = realloc(table->content_i, table->size * sizeof(int *));
      }
      table->content_i[table->tokc] = num;
      table->tokc ++;

      break;
    case STRING_TYPE:
      if (table->tokc >= table->size) {
        table->size *= 2;
        table->content_s = realloc(table->content_s, table->size * sizeof(char **));
      }
      table->content_s[table->tokc] = (char *)content;
      table->tokc ++;
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
    else if (table.type == INT_TYPE)
      printf("index %d: %d\n", i, table.content_i[i]);
  }
}

void dict_print(dictionary_t dict);

dictionary_t dict_create() {
  dictionary_t ret;
  ret.keywordc =    0;
  ret.symbolc =     0;
  ret.identifierc = 0;
  ret.constantc =   0;
  ret.literalc =    0;
  
  ret.keywordmax = KEYWORD_COUNT; 
  ret.symbolmax = SYMBOL_COUNT;
  ret.identifiermax = IDENTIFIER_COUNT;
  ret.constantmax = CONSTANT_COUNT;
  ret.literalmax = LITERAL_COUNT;


  ret.keyword_table = table_create(ret.keywordmax, STRING_TYPE);
  ret.symbol_table = table_create(ret.symbolmax, STRING_TYPE);
  ret.constant_table = table_create(ret.constantmax, INT_TYPE);
  ret.literal_table = table_create(ret.literalmax, STRING_TYPE);
  ret.identifier_table = table_create(ret.identifiermax, STRING_TYPE);
  ret.identifier_type_table = table_create(ret.identifiermax, INT_TYPE);

  return ret;
}
//returns the global index of item found. If not found, return -1
int dict_search(dictionary_t dict, int type, void *content) {

  switch (type) {
    case KEYWORD_T:
      for (int i = 0; i < dict.keyword_table.tokc; i++)
        if (strcmp ((char*)content, dict.keyword_table.content_s[i]) == 0 )
          return i;
    break;
    case SYMBOL_T:
      for (int i = 0; i < dict.symbol_table.tokc; i++)
        if (strcmp ((char*)content, dict.symbol_table.content_s[i]) == 0 )
          return i;
    break;
    case CONSTANT_T:
      for (int i = 0; i < dict.constant_table.tokc; i++)
        if (*(int*)content == dict.constant_table.content_i[i])
          return i;
    break;
    case LITERAL_T:
      for (int i = 0; i < dict.literal_table.tokc; i++)
        if (strcmp ((char*)content, dict.literal_table.content_s[i]) == 0 )
          return i;
    break;
    case IDENTIFIER_T:
      for (int i = 0; i < dict.identifier_table.tokc; i++)
        if (strcmp ((char*)content, dict.identifier_table.content_s[i]) == 0 )
          return i;
    break;
    default:
      return -1;
    break;
  }
  return -1;
}

int dict_push(dictionary_t *dict, int type, void *content) {
  int li = dict_search(*dict, type, content);
  int code;
  switch (type) {
    case KEYWORD_T:
      if (li >= 0) return li;
      table_push(&dict->keyword_table, content);
      code = dict->keywordc;
      dict->keywordc++;
      return code;
    break;
    case SYMBOL_T:
      if (li >= 0) return li+dict->keywordmax;
      table_push(&dict->symbol_table, content);
      code = dict->keywordmax + dict->symbolc;
      dict->symbolc++;
      return code;
    break;
    case CONSTANT_T:
      if (li >= 0) 
        return li+dict->keywordmax+dict->symbolmax;
      table_push(&dict->constant_table, content);
      code = dict->keywordmax+dict->symbolmax+dict->constantc;
      dict->constantc++;
      return code;
    break;
    case LITERAL_T:
      if (li >= 0) 
        return li+dict->keywordmax+dict->symbolmax+dict->constantmax;
      table_push(&dict->literal_table, content);
      code = dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalc;
      dict->literalc++;
      return code;
    break;
    case IDENTIFIER_T:
      if (li >= 0) 
        return li+dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax;
      table_push(&dict->identifier_table, content);
      code = dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax+dict->identifierc;
      dict->identifierc++;
      return code;
    break;
  }
}

int to_int(char *str) {
  int test = atoi(str);
  if (test != 0) 
    return test;
  else if (!strncmp(str, "0", 2))
      return test;
  return 0;
}
