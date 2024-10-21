#ifndef CONO_H
#define CONO_H

#define ERR          -1
#define NOOP          0
#define NEWLN         1
#define STARTDEF      2
#define ENDDEF        3
#define INPUT         4
#define PRINT         5
#define FUNCDEF       6
#define PARAM         7
#define ENDPAREN      8
#define STARTPROG     9
#define RETURN        10

#include "table.h"

void init_cono(int **ctable, dictionary_t *dict);


#endif
