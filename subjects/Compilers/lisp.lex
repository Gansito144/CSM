/*
 * lisp.lex: An example LISP scanner
 *
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

string            \"([^"\n]|\"\")+\"
integer           [0-9]+
binary            #b[0,1]*
octal             #o[0,7]*
hexadecimal       #x[0-9A-Fa-f]*
comment           ;.*
symbol            :[A-Z]+

%%
{string}        printf("string %s\n", yytext);
{integer}       printf("integer %s\n", yytext);
{binary}        printf("binary %s\n", yytext);
{octal}         printf("octal %s\n", yytext);
{hexadecimal}   printf("hexadecimal %s\n", yytext);
{comment}       printf("Comment %s\n",yytext);
{symbol}        printf("symbol %s\n",yytext);
.               printf("");
%%

/*
 * User subroutines
 */
int main()
{
  /* printf("Processing file:\n"); */
  yylex();
}
