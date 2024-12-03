#ifndef INTERP_H
#define INTERP_H

#include "table.h"

#define CONTINUE  0
#define EXIT      1
#define ERROR      1

int interpret_code(char *buffer, dictionary_t *dict, table_t *memtbl);
void live_prompt();

#endif
