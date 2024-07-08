# EBNF

_<letter>_ ::= "A" | "B" | "C" | "D" | "E" | "F" | "G"
| "H" | "I" | "J" | "K" | "L" | "M" | "N"
| "O" | "P" | "Q" | "R" | "S" | "T" | "U"
| "V" | "W" | "X" | "Y" | "Z" | "a" | "b"
| "c" | "d" | "e" | "f" | "g" | "h" | "i"
| "j" | "k" | "l" | "m" | "n" | "o" | "p"
| "q" | "r" | "s" | "t" | "u" | "v" | "w"
| "x" | "y" | "z";
_<digit>_ ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
_<symbol>_ ::= "[" | "]" | "{" | "}" | "(" | ")" | "<" | ">"
| "'" | '"' | "=" | "|" | "." | "," | ";" | "-"
| "+" | "\*" | "?" | "\n" | "\t" | "\r" | "\f" | "\b";
_<cmp_op>_ ::= "<" | ">" | "<=" | ">=" | "==";
_<logical_op>_ ::= "&&" | "||";

_<character>_ ::= _<letter>_ | _<digit>_ | _<symbol>_;
_<terminator>_ ::= ";" | ".";
_<type>_ ::= "int" | "bool" | "char" | "string" | "void" | "float";
_<token>_ ::= _<identifier>_ | _<keyword>_ | _<type>_ | _<literal>_ | _<separator>_ | _<operator>_;
_<identifier>_ ::= _<letter>_ (_<letter>_ | _<digit>_ | "\_")\*;
_<condition>_ ::= _<expr>_ _<cmp_op>_ _<expr>_;

## TODO: add assignment

## NOTE: may change as needed

_<paren_condition>_ ::= "(" _<condition>_ ")"
_<if_statement>_ ::= "if" _<paren_condition>_ "{" (_<statement>_)_ "}"
*<if_else_statement>* ::= *<if_statement>* "else" "{" (*<statement>*)_ "}"
_<statement>_ ::= (_<if_statement>_ | _<if_else_statement>_)\*

_<program>_ = _<statement>_+;
