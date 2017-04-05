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
atom			  ({alpha_num}|{digit}|{str}|{symbol}) 
integer           [0-9]*
binary            #b[0-1]*
octal             #o[0-7]*
hexadecimal       #x[0-9A-Fa-f]*
single_comment    \;.*
block_comment     "#|"([^*]|(\|+[^|#]))*\|+\#
expression        \(.+\)
greater_than      >
less_than         <
greater_equal     <=
less_equal        >=
cmp_word          min|max|equal|equalp|eq|eql
rt_evaluation     eval
nil               nil
logical           not|and|or
type_boolean      boolean
var_assignment    setq|setf|set|let    
comparisson       {greater_than}|{less_than}|{cmp_word}
declare           \(defpackage p*\)
selective_export  \(export *\)
import            \(use\-package *\)
import_package    \(require *\)
import_selective  \(import *\)
package_scope     :.::

/*
 * Reserved Words
 */

r_lambda                "lambda"
r_defun	                "defun"
r_funcall               "funcall"
r_return                "return"
r_identity              "identity"
r_return_from	          "return-from"
r_no_applicable_method  "no-applicable-method"
r_apply					        "apply"
%%

{integer}           printf("(integer) (%s)\n", yytext);
{binary}            printf("(binary) (%s)\n", yytext);
{octal}             printf("(octal) (%s)\n", yytext);
{hexadecimal}       printf("(hexadecimal) (%s)\n", yytext);
{single_comment}    printf("(Simple comment) (%s)\n", yytext);
{block_comment}     printf("(Block comment) (%s)\n", yytext);
{atom}      		    printf("(atom) (%s)\n", yytext);
{expression}        printf("(expression) (%s)\n", yytext);
{comparisson}       printf("(comparisson) (%s)\n", yytext);
{logical}           printf("(logical) (%s)\n", yytext);
.                   printf("");
%%

/*
 * User subroutines
 */
int main()
{
  /* printf("Processing file:\n"); */
  yylex();
}
