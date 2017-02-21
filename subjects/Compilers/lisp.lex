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

white_space       [ \t]*
digit             [0-9]
alpha             [A-Za-z_]
alpha_num         ({alpha}|{digit})
hex_digit         [0-9A-F]
identifier        {alpha}{alpha_num}*
unsigned_integer  {digit}+
hex_integer       0[xX]{hex_digit}{hex_digit}*
exponent          e[+-]?{digit}+
i                 {unsigned_integer}
real              ({i}\.{i}?|{i}?\.{i}){exponent}?
string            \'([^'\n]|\'\')+\'
bad_string        \'([^'\n]|\'\')+

%%
{hex_integer}   printf("Found a HEX number %s !", yytext);
.   printf("");
%%

/*
 * User subroutines
 */
int main()
{
  printf("Give me your input:\n");
  yylex();
}
