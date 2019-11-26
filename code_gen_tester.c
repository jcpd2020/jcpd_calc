#include <ctap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code_gen.h"
#define MAXCHAR 1000

TESTS{
    plan(12);    //Num of tests running
    char *op_input_pointer = "3";
    is(operatorSwitching(op_input_pointer), "Error", "3 is not an Operator, Error should be returned");
    is(operatorSwitching("/"), "dv", "'/' is an operator so 'dv' should be returned");
    is(operatorSwitching("+"), "ad", "+ is a float, so the resulting assembly code should be 'ad'");


    char *float_pointer="4.05";
    ok(isFloat(float_pointer) == 1, "4.05 is a float, isFloat should return 1");
    char *float_fail="-109";
    ok(isFloat(float_fail)==0, "-109 is not a float, isFloat should return 0");


    char temp[2];
    char *num_test="-34";
    char *first_char = &(num_test[0]);
    strncpy(temp, first_char, 1); 
    temp[1] = '\0';

    ok(isNumber(num_test, temp) ==1, "-34 is a number so 1 should be returned");

    char temp_fail[2];
    char *num_test_fail="ab5.78346665555";
    char *first_char2 = &(num_test_fail[0]);
    strncpy(temp_fail, first_char2, 1); 
    temp_fail[1] = '\0';

    ok(isNumber(num_test_fail, temp_fail) ==0, "The letters at the start of 'ab5.78..' results in a 0 being returned. Not a number");

    //write to a file 
    //run the test on the file - generate_code();
    FILE * test_file;
    char line[MAXCHAR];


    char filename[] = "test_file";
    test_file = fopen(filename, "w");
    fprintf(test_file, "10\n-5\n+\n^\n2.44");
    fclose(test_file);
    generate_code(filename);

    char * tokens[5];
    test_file = fopen("test_file", "r");
    
    tokens[0] = "li 10\n";
    tokens[1] = "li -5\n";
    tokens[2] = "ad\n";
    tokens[3] = "ex\n";
    tokens[4] = "lf 2.44";

    int i = 0;
    while (fgets(line, MAXCHAR, test_file)) {
        is(line, tokens[i], "line has been converted correctly");
        i += 1;
    }



}
