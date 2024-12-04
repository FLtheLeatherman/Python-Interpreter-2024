parser grammar Python3Parser;

options {
  tokenVocab = Python3Lexer;
}

file_input: (NEWLINE | stmt)* EOF;
funcdef: 'def' NAME parameters ':' suite;
parameters: '(' typedargslist? ')';
typedargslist: (tfpdef ('=' test)? (',' tfpdef ('=' test)?)*);
tfpdef: NAME ;

stmt: simple_stmt | compound_stmt;
simple_stmt: small_stmt  NEWLINE;
small_stmt: expr_stmt | flow_stmt;
expr_stmt: testlist ( (augassign testlist) |
                     ('=' testlist)*);//连等 加等/减等/...
augassign: ('+=' | '-=' | '*=' | '/=' | '//=' | '%=' );
flow_stmt: break_stmt | continue_stmt | return_stmt;
break_stmt: 'break';
continue_stmt: 'continue';
return_stmt: 'return' (testlist)?;
compound_stmt: if_stmt | while_stmt | funcdef ;
if_stmt: 'if' test ':' suite ('elif' test ':' suite)* ('else' ':' suite)?;
while_stmt: 'while' test ':' suite;
suite: simple_stmt | NEWLINE INDENT stmt+ DEDENT;
test: or_test ;
or_test: and_test ('or' and_test)*;
and_test: not_test ('and' not_test)*;
not_test: 'not' not_test | comparison;
comparison: arith_expr (comp_op arith_expr)*;
comp_op: '<'|'>'|'=='|'>='|'<=' | '!=';
arith_expr: term (addorsub_op term)*;
addorsub_op: '+'|'-';
term: factor (muldivmod_op factor)*;
muldivmod_op: '*'|'/'|'//'|'%';
factor: ('+'|'-') factor | atom_expr;
atom_expr: atom trailer?;
trailer: '(' (arglist)? ')' ;
atom: (NAME | NUMBER | STRING+| 'None' | 'True' | 'False' | ('(' test ')') | format_string);
format_string: FORMAT_QUOTATION (FORMAT_STRING_LITERAL | '{' testlist '}')* QUOTATION;
testlist: test (',' test)* (',')?;//算式  eg： a,b   a   a+b
arglist: argument (',' argument)*  (',')?;
argument: ( test |
            test '=' test );
