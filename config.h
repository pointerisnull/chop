#ifndef CONFIG_H
#define CONFIG_H

#define MAX_PATH 256
/*KEYWORD -> SYMBOL -> CONSTANT -> LITERAL -> IDENTIFIER*/
#define KEYWORD_COUNT 32
#define SYMBOL_COUNT 32
#define CONSTANT_COUNT 1024
#define LITERAL_COUNT 128
#define IDENTIFIER_COUNT 1024

#define SYM_NEWLINE "\n"
#define SYM_COMMA   ","
#define SYM_PLUS    "+"
#define SYM_MINUS   "-"
#define SYM_STAR    "*"
#define SYM_FSLASH  "/"
#define SYM_BSLASH  "\\"
#define SYM_EQUALS  "="
#define SYM_MODULO  "%"
#define SYM_NOT     "!"
#define SYM_ADDR    "&"
#define SYM_PIPE    "|"
#define SYM_COMMENT "#"
#define SYM_STRLIT  "\""
#define SYM_LESS    "<"
#define SYM_GREATER ">"
#define SYM_LPAREN  "("
#define SYM_RPAREN  ")"
#define SYM_LBRACK  "["
#define SYM_RBRACK  "["
#define SYM_EQUIV   "=="
#define SYM_GEQUIV  ">="
#define SYM_LEQUIV  "<="
#define SYM_PP      "++"
#define SYM_MM      "--"
#define SYM_PEQUALS "+="
#define SYM_MEQUALS "-="

#define KEYWORD_NULL    "NULL"
#define KEYWORD_VOID    "VOID"
#define KEYWORD_BEGIN   "BEGIN"
#define KEYWORD_RETURN  "RETURN"
#define KEYWORD_IMPORT  "IMPORT"
#define KEYWORD_IF      "IF"
#define KEYWORD_ELSE    "ELSE"
#define KEYWORD_THEN    "THEN"
#define KEYWORD_FOR     "FOR"
#define KEYWORD_NEXT    "NEXT" //end of for loop
#define KEYWORD_WHILE   "WHILE"
#define KEYWORD_LOOP    "LOOP" //WEND in basic, end of while
#define KEYWORD_PRINT   "PRINT"
#define KEYWORD_INPUT   "INPUT"
#define KEYWORD_i8      "BIT8"
#define KEYWORD_i16     "BIT16"
#define KEYWORD_i32     "BIT32"
#define KEYWORD_i64     "BIT64"


#endif
