#include <ctap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokeniser.h"

//gcc -o tok_test.t tokeniser_tester.c tokeniser.c
//prove ./tok_test.t

TESTS{
    
    char test_tokens[1000][1000];
    
    //plan(10);
    //Test that the isOperator function for the tokeniser works correctly. It should return 0 if the string is not an operator, and 1 if it is
    char *op_input_pointer = "3";
    ok(isOperator(op_input_pointer) == 0, "3 is not an Operator");
    ok(isOperator("-22") == 0, "-22 is not an Operator");
    ok(isOperator("-") == 1, "- is an Operator");
    
    //Test the string concatonator 
    char *str1 = "2";
    char *str2 = "7";
    is(concater(str1, str2), "27", "2 joined with 7 should make 27");
    is(concater("-", "1"), "-1", "- joined with 1 should make -1");
    is(concater("-31", "5"), "-315", "-31 joined with 5 should make -315");
    is(concater("104", str2), "1047", "104 joined with 7 should make 1047");
    
    //Test saving a character to the appropriate token slot
    char test_input_str[1000] = "121-6";
    int test_token_counter = 0;
    char test_temp[2];
    saveToken(0, test_input_str, test_tokens, &test_token_counter, test_temp);
    saveToken(1, test_input_str, test_tokens, &test_token_counter, test_temp);
    saveToken(2, test_input_str, test_tokens, &test_token_counter, test_temp);
    is(test_tokens[0], "121", "First token should be 121");
    
    test_token_counter++;
    saveToken(3, test_input_str, test_tokens, &test_token_counter, test_temp);
    is(test_tokens[1], "-", "Second token should be a -");
    
    test_token_counter++;
    saveToken(4, test_input_str, test_tokens, &test_token_counter, test_temp);
    is(test_tokens[2], "6", "Third token should be a 6");
    
    //Test the writing to line function
    FILE *file_pointer;
    char line[256];
    writeToFile(file_pointer, test_token_counter, test_tokens);
    
    int test_total_tokens = test_token_counter;
    test_token_counter = 0;
    file_pointer = fopen("useroutput.txt", "r");
    
    while (fgets(line, 1000, file_pointer)){
        //remove the newline character at the end of each line read from a file
        line[strlen(line)-1] = '\0';
        is(test_tokens[test_token_counter], line, "Compare the token to the line");
        test_token_counter++;
    }
    fclose(file_pointer);
    
    //Test that the whole tokeniser works, from start to finish
    file_pointer = fopen("userinput.txt", "w");
    fprintf(file_pointer, "%s\n", "21 * -34/87^2 + 8(67%3)"); 
    fclose(file_pointer);
    
    char final_test_tokens[1000][1000];
    int total_test_tokens = tokenise(final_test_tokens);
    writeToFile(file_pointer, total_test_tokens, final_test_tokens);
    test_token_counter = 0;
    file_pointer = fopen("useroutput.txt", "r");
    while (fgets(line, 1000, file_pointer)){
        //remove the newline character at the end of each line read from a file
        line[strlen(line)-1] = '\0';
        is(final_test_tokens[test_token_counter], line, "Compare the token in the final token list to the line");
        test_token_counter++;
    }
    fclose(file_pointer);
        
    
    
    
	
}
