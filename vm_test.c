/* author: David Ryan-Lynch, 115310721 */


#include <ctap.h>
#include <stdio.h>
#include "stack.h"
#include "vm.h"

TESTS {

    // stack test

    plan(14);

    ok(is_empty() == 1, "Stack should be considered empty with nothing in it");
    ok(is_full() == 0, "Stack should not be full with less than max items in it");
    ok(pop() == -0, "Empty stack should return -0");

    float test_float_1 = 10.0f;
    float test_float_2 = 5.0f;

    push(test_float_1);
    push(test_float_2);
    ok(pop() == test_float_2, "FILO should be observed");
    ok(pop() == test_float_1, "FILO should be observed");

    push(test_float_1);
    push(test_float_2);
    do_add();
    ok(pop() == 15.0f, "10 + 5 should be 15");

    push(test_float_1);
    push(test_float_2);
    do_subtract();
    ok(pop() == 5.0f, "10 - 5 should be 5");

    push(test_float_1);
    push(test_float_2);
    do_multiply();
    ok(pop() == 50.0f, "10 * 5 should be 50");

    push(test_float_1);
    push(test_float_2);
    do_divide();
    ok(pop() == 2.0f, "10 / 5 should be 2");

    push(test_float_1);
    push(test_float_2);
    do_exponential();
    ok(pop() == 100000.0f, "10 ^ 5 should be 100,000");

    push(test_float_1);
    push(test_float_2);
    do_modulus();
    ok(pop() == 0.0f, "10 % 5 should be 0");

    // vm test

    char * test_opcode = (char *) malloc(3);
    float test_number;

    char * test_line_1 = "lf 50.55";
    char * test_line_2 = "li 20";
    char * test_line_3 = "ad";

    grab_opcode(test_line_1, test_opcode);
    grab_number(test_line_1, &test_number);
    is(test_opcode, "lf", "Opcode should have been parsed from line as lf");
    ok(test_number == 50.55f, "Number should have been parsed from line as 50.55");

    do_instruction(test_line_1);
    do_instruction(test_line_2);
    do_instruction(test_line_3);
    ok(pop() == 70.55f, "Instructions should have calculated answer to be 70.55");

    free(test_opcode);


}
