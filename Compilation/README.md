
Basic specification for the language.

## Discussion about (anti-)features (this section should remain confidential)

* simple tokens (easy lexer, because lexers are boring)
* complex grammar
  * no mandatory parentheses, no separator
  * parentheses for value expression, boolean expression and blocks of statement (instead of brackets)
  * `=` is both assignment and comparison
  * comparison can be combined `a = b = c` means `a = b && b = c`
  * => should be hasr to parse with dirty regexp or a manual recursive ll parser. Most tools should be able to deal with the language.
* doable evaluation
  * standard statement and expressions
  * the combined comparisons is the most tricky
* possible compiler to C
  * generating C code is mainly trivial
  * the combined comparisons is the most tricky

## Syntax

Program files are ASCII 7 bits.

Characters <= 32 are ignored and considered valid separators.

Keywords `print`, `byte`, `println`, `while`, `if`, `read` and `not`.
They are case-sensitive, reserved and unusable as identifier
Other sequence of letters (a-z and A-Z) are valid identifier (no digit)

Sequence of digits are considered a literal number

## Program and Statements

A program is made of a sequence of statements

### Assignment

syntax: `*identifier* = *value*`

examples:

~~~
a = 5
foo = a + 5
~~~

### Printing

syntaxes: `print *string*` or `print [byte] value` or `println`

examples:

~~~
print "hello"
print 42
print byte 42
println
~~~

### Sequence

Sequences of statements are executed in order

exemples:

~~~
a = 1 print "a=" print a println
a=1print"a="print a println
~~~

Multiple statements can be grouped together with parentheses

~~~
(a = 1 print "a=" print a println)
~~~

### While

syntax: `while *condition* *statement*`

example:

~~~
a = 5
while a>0 (print "*" a = a - 1)
~~~

### If

syntax: `if *condition* *statement* [else *statement*]`

example:

~~~
a = 5
if a > 0 print "ok"
if a < 0 print "fail"
if a = 5 print "ok" else print "fail"
~~~

## Values

values are signed integers with at least 16 bits of precision.

### Literal

can be standard decimal representation or ASCII 7 bits character (ascii code is used)

### Variables

scope is global.
using a unassigned variable is undefined.

### Basic arithmetic operators

* infix binary operators + - * /
* the unary - for the negation.
* parenthese for grouping an priority
* Standard priority and associativity.

### Read

syntax `read` and `read byte`

## Contition

### Comparaison

syntax: `*value* [*op* *value*]+`

where op is on of = != < <= > >=

examples

~~~
a = 1
b = 2
if a = 1 != b < 4 print "ok"
if a = 1 != b = 4 print "fail"
~~~

### Boolean operations

The three booleam operators `||`, `&&` and `not` can be used.
precedence is left to right, `||` begin the least and `not` the most.
PArentherses can bu used for grouping and priority again.

examples:

~~~
a = 5
if a > 2 && a < 7 print "ok"
if not (a < 2 || a > 7) print "ok"
~~~
