#include <ctap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokeniser.h"
#define MAXCHAR 1000

TESTS{
    
    //First test. 32 + 6
    
    file_pointer = fopen("jcpd.io", "w");
    fprintf(file_pointer, "%s\n", "32 + 6"); 
    fclose(file_pointer);
    
    //The tokeniser is run
    char final_test_tokens[MAXCHAR][MAXCHAR];
    int total_test_tokens = tokenise(final_test_tokens);
    writeToFile(file_pointer, total_test_tokens, final_test_tokens);
    
    //The infix to postfix converter is run
    
    //The code generator is run
    
    //The virtual machine is run
    
    test_token_counter = 0;
    file_pointer = fopen("jcpd.io", "r");
    fgets(line, MAXCHAR, file_pointer);
    line[strlen(line)-1] = '\0';
    is("38", line, "Compare the result of the calculation to what it should be. £2 + 6 = 38");
    fclose(file_pointer);
       
}
