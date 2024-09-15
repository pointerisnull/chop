#ifndef LEXER_H
#define LEXER_H

static char DELIMITERS[] = " \n\t\r\v\f,;+-*/=%!@&|#<>()[]";

char **split(const char *str, const char *delimiters, int *count);
void debug_print(char **buffer, int count);
void free_split_string(char **buffer, int tokc);

#endif
