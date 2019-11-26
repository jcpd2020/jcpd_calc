#include <ctap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i2p.h"

TESTS{
    //plan();
    //test the isOperatorI2P function in 
    ok(isOperatorI2P("-") == 1, "- is an OP");
    ok(isOperatorI2P("-10") == 0, "-10 is a number not an operator");
    ok(isOperatorI2P("a") == 0, "not a valid operator");
    
    
    //Test the readFile function, which reads from a file into a buffer
    FILE *file_pointer;
    char line[1000];
    char file_inputs[100][100];
    int file_input_char = 0;
    
    file_pointer = fopen("jcpd.io", "w");
    fprintf(file_pointer, "%s\n", "20");
    fprintf(file_pointer, "%s\n", "*");
    fprintf(file_pointer, "%s", "31.4");
    fclose(file_pointer);
    
    readFile(file_pointer, line, file_inputs, &file_input_char);
    file_pointer = fopen("jcpd.io", "r");
    file_input_char = 0;
    while (fgets(line, 1000, file_pointer)){
        //remove the newline character at the end of each line read from a file
        line[strlen(line)-1] = '\0';
        is(file_inputs[file_input_char], line, "Compare the token to the line");
        file_input_char++;
    }
    
    fclose(file_pointer);
    
    
    
    //test the op importance function
    char *op = "*";
    ok(decideOpImportance(op) == 2, "* has an importance of 2");
    op = "/";
    ok(decideOpImportance(op) == 2, "* has an importance of 2");
    op = "-";
    ok(decideOpImportance(op) == 1, "* has an importance of 2");
    op = "+";
    ok(decideOpImportance(op) == 1, "* has an importance of 2");
    op = "%";
    ok(decideOpImportance(op) == 2, "* has an importance of 2");
    op = "^";
    ok(decideOpImportance(op) == 3, "* has an importance of 2");
    
    
    //Test that the stack is organized properly by the organiseStack method by calling the main of the i2p 
    file_pointer = fopen("jcpd.io", "w");
    fprintf(file_pointer, "%s\n", "32");
    fprintf(file_pointer, "%s\n", "*");
    fprintf(file_pointer, "%s\n", "77");
    fprintf(file_pointer, "%s\n", "^");
    fprintf(file_pointer, "%s\n", ".13");
    fprintf(file_pointer, "%s\n", "+");
    fprintf(file_pointer, "%s\n", "9");
    fclose(file_pointer);
    
    infixToPostfix();
    
    file_pointer = fopen("jcpd.io", "r");
    fgets(line, 1000, file_pointer);
    line[strlen(line)-1] = '\0';
    is(line, "32", "checking postfix line");
    fgets(line, 1000, file_pointer);
    line[strlen(line)-1] = '\0';
    is(line, "77", "checking postfix line");
    fgets(line, 1000, file_pointer);
    line[strlen(line)-1] = '\0';
    is(line, ".13", "checking postfix line");
    fgets(line, 1000, file_pointer);
    line[strlen(line)-1] = '\0';
    is(line, "^", "checking postfix line");
    fgets(line, 1000, file_pointer);
    line[strlen(line)-1] = '\0';
    is(line, "*", "checking postfix line");
    fgets(line, 1000, file_pointer);
    line[strlen(line)-1] = '\0';
    is(line, "9", "checking postfix line");
    fgets(line, 1000, file_pointer);
    line[strlen(line)-1] = '\0';
    is(line, "+", "checking postfix line");
    fgets(line, 1000, file_pointer);
    line[strlen(line)-1] = '\0';
    fclose(file_pointer);
}
