/*
    Name:   Jack Curtin
    Student ID: 117359191
*/

#include<stdio.h>
#include <string.h>

int isOperatorI2P(char *maybe_op){
    /*
    *   The input ...
    *   Checks input token to determine if it is an operand or an operator. 
    *   It returns ... 
    */
    char op = *maybe_op;
    char op_temp[2];
    char *op_temp_pointer = op_temp;
    strncpy(op_temp, maybe_op, 2);
    /*
    *
    * 
    */

    if((*(op_temp_pointer+1) == '\0') && ((*op_temp_pointer == '-') || (*op_temp_pointer == '+') || (*op_temp_pointer == '^') || (*op_temp_pointer == '/') || (*op_temp_pointer == '*') || (*op_temp_pointer == '%') || (*op_temp_pointer == '(') || (*op_temp_pointer == ')'))){
        return 1;
    }
    return 0;
}

void writeFile(FILE *file_pointer, char file_inputs[100][100], int *file_input_counter_ptr){
    /*
    *   Writes the speificed token to output file.
    * 
    * 
    */
}

void readFile(FILE *file_pointer, char line[1000], char file_inputs[100][100], int *file_input_counter_ptr){
    /*
    *
    * 
    */
    //printf("%s\n","Look");
    file_pointer = fopen("jcpd.io", "r");
    char *maybe_op;
    int line_pointer = 0;
    int new_file_counter = 0;
    while (fgets(line, 1000, file_pointer)){
        /*
        * remove the newline character at the end of each line read from a file
        */
        line[strlen(line)-1] = '\0';
        strcpy(file_inputs[*file_input_counter_ptr], line);
        (*file_input_counter_ptr)++;
    }
    fclose(file_pointer);
}

int decideOpImportance(char *op){
    /*
    *
    * 
    * 
    */
    if((*op == '^')){
        return 3;
    }
    
    else if((*op == '*') || (*op == '/') || (*op == '%')){
        return 2;
    }
    
    else if((*op == '+') || (*op == '-')){
        return 1;
    }
    //return 0;    
}

void organiseStack(FILE *file_pointer, char stack[20][20], int stack_counter, int *stack_counter_ptr, char file_inputs[100][100], int *file_input_counter_ptr){
    /*
    *
    * 
    * 
    * 
    */
    file_pointer = fopen("jcpd.io", "w");
    char *current_op;
    char current_op_prec = 0;
    for(int index=0; index<*file_input_counter_ptr; index++){
        if(isOperatorI2P(file_inputs[index])){
            if((*file_inputs[index] == '/') || (*file_inputs[index] == '*') || (*file_inputs[index] == '+') || (*file_inputs[index] == '-') || (*file_inputs[index] == '^') || (*file_inputs[index] == '%') || (*file_inputs[index] == '(') || (*file_inputs[index] == ')')){   
                
                if((*file_inputs[index] == '(') || (*file_inputs[index] == ')')){}
                
                else if((*stack_counter_ptr == 0) || (decideOpImportance(file_inputs[index]) > decideOpImportance(stack[*stack_counter_ptr-1]))){                    
                    strcpy(stack[*stack_counter_ptr], file_inputs[index]);
                    (*stack_counter_ptr)++;                    
                    current_op = file_inputs[index];
                    current_op_prec = decideOpImportance(file_inputs[index]);
                }
                
                else{
                    (*stack_counter_ptr)--;
                    while(decideOpImportance(file_inputs[index]) <= decideOpImportance(stack[*stack_counter_ptr])){
                        fprintf(file_pointer, "%s\n", stack[*stack_counter_ptr]);
                        (*stack_counter_ptr)--;
                        if(*stack_counter_ptr <= -1){
                            break;
                        }
                    }
                    (*stack_counter_ptr)++;
                    strcpy(stack[*stack_counter_ptr], file_inputs[index]);
                    (*stack_counter_ptr)++;
                }
            }
        }
        
        else{
            fprintf(file_pointer, "%s\n", file_inputs[index]);
        }
    }
    (*stack_counter_ptr)--;
    while(*stack_counter_ptr >= 0){
        fprintf(file_pointer, "%s\n", stack[*stack_counter_ptr]);
        (*stack_counter_ptr)--;
    }
    fclose(file_pointer);    
}

void infixToPostfix(){
    /*
    *
    * 
    */
	char exp[20];
	char* e, x;
    char line[1000];
    FILE *file_pointer;
    int stack_counter = 0;
    int *stack_counter_ptr = &stack_counter;
    char stack[20][20];
    char file_inputs[100][100];
    int file_input_counter = 0;
    readFile(file_pointer, line, file_inputs, &file_input_counter);
    organiseStack(file_pointer, stack, stack_counter, stack_counter_ptr, file_inputs, &file_input_counter);
}
