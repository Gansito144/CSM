#!/bin/bash

# echo 'Generating... flex lisp.lex'
flex lisp.lex
# echo 'Compiling... gcc lex.yy.c -o scanner'
g++ lex.yy.c -o scanner
echo 'Processing file resources/${1}'
echo ' ------------------------------------------ '
echo '|             BEGIN OF FILE                |'
echo '------------------------------------------ '
cat resources/${1}
echo '\n------------------------------------------ '
echo '|               END OF FILE               |'
echo '------------------------------------------ '
echo '\n'
echo '\n------------------------------------------ '
echo '|        ** BEGIN OF SCANNER **           |'
echo '------------------------------------------ '
./scanner < resources/${1}
echo '\n------------------------------------------ '
echo '|        **  END OF SCANNER **            |'
echo '------------------------------------------ '
