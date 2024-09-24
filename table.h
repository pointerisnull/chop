#ifndef TABLE_H
#define TABLE_H

#define INT_TYPE 0
#define STRING_TYPE 1

typedef struct table_t {
  int type;
  int size;
  int tokc;
  char **content_s;
  int *content_i;
} table_t;

typedef struct dictionary_t {
  int keywordc;
  int symbolc;
  int identifierc;
  int constantc;
  int literalc;
  table_t keyword_table;
  table_t symbol_table;
  table_t identifier_table;
  table_t identifier_type_table;
  table_t constant_table;
  table_t literal_table;

} dictionary_t;

void table_push(table_t *table, void *content);
table_t table_create(int size, int type);
void table_free(table_t *table);
void table_print(table_t table);

dictionary_t dict_create();
void dict_print(dictionary_t dict);

#endif
