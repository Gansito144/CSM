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
digit             [0-9]+
alpha             [A-Za-z_]
alpha_num         ({alpha}|{digit})
str               \"[^\"\n]*\"
atom			  ({alpha_num}|{digit}|{str}) 
integer           [0-9]*
binary            #b[0,1]*
octal             #o[0,7]*
hexadecimal       #x[0-9A-Fa-f]*
start_comment1    ";"+
start_comment2    "#|"+
end_comment2      "|#"+

%%
{integer}        printf("integer %s\n", yytext);
{binary}         printf("binary %s\n", yytext);
{octal}          printf("octal %s\n", yytext);
{hexadecimal}    printf("hexadecimal %s\n", yytext);
.   printf("");
{start_comment1} printf("Simple comment %s\n", yytext);
{start_comment2} printf("Block comment %s\n", yytext);
{end_comment2}   printf("End Block comment %s\n", yytext);
{atom}    		 printf("atom %s\n", yytext);
%%

/*
 * User subroutines
 */
int main()
{
  printf("Give me your input:\n");
  yylex();
}
