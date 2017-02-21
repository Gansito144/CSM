## Sample LISP Scanner

### Description: 

### Usage:
#### Manual
 * flex lisp.lex
 * gcc lex.yy.c -o scanner
 * ./scanner < resources/sample.lisp
#### Script
 * Just run `source run.sh <file>`
 Where *file* is one of the resources provided, e.j. `source run.sh sample.lisp`

### Requirements
In MacOS please run: `brew install flex`.


