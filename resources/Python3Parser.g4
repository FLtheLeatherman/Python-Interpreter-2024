parser grammar Python3Parser;

options {
  tokenVocab = Python3Lexer;
}

file_input: (NEWLINE | stmt)* EOF; // done
funcdef: 'def' NAME parameters ':' suite; // done
parameters: '(' typedargslist? ')'; // done
typedargslist: (tfpdef ('=' test)? (',' tfpdef ('=' test)?)*);
tfpdef: NAME ; // done

stmt: simple_stmt | compound_stmt; // done
simple_stmt: small_stmt  NEWLINE; // done
small_stmt: expr_stmt | flow_stmt; // done
expr_stmt: testlist ( (augassign testlist) | ('=' testlist)*);//连等 加等/减等/... // done
augassign: ('+=' | '-=' | '*=' | '/=' | '//=' | '%=' ); // done
flow_stmt: break_stmt | continue_stmt | return_stmt; // done
break_stmt: 'break'; // done
continue_stmt: 'continue'; // done
return_stmt: 'return' (testlist)?; // done
compound_stmt: if_stmt | while_stmt | funcdef ; // done
if_stmt: 'if' test ':' suite ('elif' test ':' suite)* ('else' ':' suite)?; // done
while_stmt: 'while' test ':' suite; // done
suite: simple_stmt | NEWLINE INDENT stmt+ DEDENT; // done
test: or_test ; // done
or_test: and_test ('or' and_test)*; // done
and_test: not_test ('and' not_test)*; // done
not_test: 'not' not_test | comparison; // done
comparison: arith_expr (comp_op arith_expr)*; // done
comp_op: '<'|'>'|'=='|'>='|'<=' | '!='; // done
arith_expr: term (addorsub_op term)*; // done
addorsub_op: '+'|'-'; // done
term: factor (muldivmod_op factor)*; // done
muldivmod_op: '*'|'/'|'//'|'%'; // done
factor: ('+'|'-') factor | atom_expr; // done
atom_expr: atom trailer?; // done, except for functions
trailer: '(' (arglist)? ')' ; // done
atom: (NAME | NUMBER | STRING+| 'None' | 'True' | 'False' | ('(' test ')') | format_string); // done
format_string: FORMAT_QUOTATION (FORMAT_STRING_LITERAL | '{' testlist '}')* QUOTATION; // done
testlist: test (',' test)* (',')?;//算式  eg： a,b   a   a+b // done
arglist: argument (',' argument)*  (',')?; // done
argument: ( test | test '=' test ); // done
