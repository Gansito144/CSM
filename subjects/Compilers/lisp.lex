/*
 * lisp.lex: An example LISP scanner
 * @Author: Diego Alejandro Cruz Ramirez 
 * @Author: Ulises Mendez Martinez
 */

/* 
 * To avoid compilation error message.
 * http://stackoverflow.com/a/2612449 
 */
%option noyywrap 

/*
 * Declarations
 */

%{
#include <stdio.h>
%}

white_space       [ \t]*
digit             [0-9]+
alpha             [A-Za-z_]
symbol            \:[A-Z]*
alpha_num         ({alpha}|{digit})
str               \"[^\"\n]*\"
atom			        ({alpha_num}|{digit}|{str}|{symbol}) 
integer           [0-9]*
binary            #b[0-1]*
octal             #o[0-7]*
hexadecimal       #x[0-9A-Fa-f]*
single_comment    ";".*
block_comment     "#|"([^*]|(\|+[^|#]))*\|+\#
expression        \(.+\)

%%
{integer}           printf("(integer) (%s)\n", yytext);
{binary}            printf("(binary) (%s)\n", yytext);
{octal}             printf("(octal) (%s)\n", yytext);
{hexadecimal}       printf("(hexadecimal) (%s)\n", yytext);
.                   printf("");
{single_comment}    printf("(Simple comment) (%s)\n", yytext);
{block_comment}     printf("(Block comment) (%s)\n", yytext);
{atom}    		      printf("(atom) (%s)\n", yytext);
{expression}        printf("(expression) (%s)\n", yytext);
%%

/*
 * User subroutines
 */
int main()
{
  /* printf("Processing file:\n"); */
  yylex();
}
