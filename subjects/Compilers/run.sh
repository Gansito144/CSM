#!/bin/bash

echo 'Generating... flex lisp.lex'
flex lisp.lex
echo 'Compiling... gcc lex.yy.c -o scanner'
gcc lex.yy.c -o scanner
echo 'Executing...  ./scanner < resources/${1}'
./scanner < resources/${1}