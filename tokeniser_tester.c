#include <ctap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokeniser.h"

//gcc -o tok_test.t tokeniser_tester.c tokeniser.c
//prove ./tok_test.t
TESTS{
    
    //plan(4);
    //Ensure that the isOperator function for the tokeniser works correctly. It should return 0 if the string is not an operator, and 1 if it is
    char *op_input_pointer = "3";
    ok(isOperator(op_input_pointer) == 0, "3 is not an Operator");
    op_input_pointer = "-33";
    ok(isOperator(op_input_pointer) == 0, "-22 is not an Operator");
    op_input_pointer = "-";
    ok(isOperator(op_input_pointer) == 1, "- is an Operator");
    
    
    
	
}
