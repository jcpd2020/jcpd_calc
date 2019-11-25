#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
//int top = -1;
/*void push(char x)
{
	stack[++top] = x;
}*/

/*char pop()
{
	if (top == -1)
		return -1;
	else
		return stack[top--];
}*/

/*char *concater(char *str1, char *str2){
    int length = strlen(str1) + strlen(str2);
    char *result = (char *) malloc(sizeof(char) * (length + 1));

    int j = strlen(str1);
    int i;
    for (i=0; i<strlen(str1); i++){
        result[i] = str1[i];
    }

    for (i=0; i<strlen(str2); i++){
        result[i+j] = str2[i];
    }

    result[(strlen(str1) + strlen(str2) + 1)] = '\0';
    return result;
}*/

/*void saveToken(char op[MAXCHAR], char tokens[MAXCHAR][MAXCHAR], int *token_counter_ptr, char temp[2]){
    char *res;
    char *character1 = tokens[*token_counter_ptr];
    char *character2 = &(str[i]);
    strncpy(temp, character2, 1);
    res = concater(character1, &temp[0]);
    strcpy(tokens[*token_counter_ptr], res);
    free(res);
}*/

/*
int priority(char x)
{
	if (x == '(')
		return 0;
	if (x == '+' || x == '-')
		return 1;
	if (x == '*' || x == '/' || x == '%')
		return 2;
	if (x == '^')
		return 3;
}
*/

int isOperatorI2P(char *maybe_op){
    char op = *maybe_op;
    char op_temp[2];
    char *op_temp_pointer = op_temp;

    strncpy(op_temp, maybe_op, 2);

    if((*(op_temp_pointer+1) == '\0') && ((*op_temp_pointer == '-') || (*op_temp_pointer == '+') || (*op_temp_pointer == '^') || (*op_temp_pointer == '/') || (*op_temp_pointer == '*') || (*op_temp_pointer == '%') || (*op_temp_pointer == '(') || (*op_temp_pointer == ')'))){
        return 1;
    }

    return 0;
}

void writeFile(FILE *file_pointer, char file_inputs[100][100], int *file_input_counter_ptr){
    
    
}

void readFile(FILE *file_pointer, char line[1000], char file_inputs[100][100], int *file_input_counter_ptr){
    file_pointer = fopen("jcpd.io", "r");
    char *maybe_op;
    int line_pointer = 0;
    int new_file_counter = 0;
    while (fgets(line, 1000, file_pointer)){
        //remove the newline character at the end of each line read from a file
        line[strlen(line)-1] = '\0';
        //printf("Removed newline from: %s\n", line);
        strcpy(file_inputs[*file_input_counter_ptr], line);
        //printf("%s\n", "copied line to buffer");
        //printf("First item in buffer: %s\n", file_inputs[*file_input_counter_ptr]);
        (*file_input_counter_ptr)++;
        //printf("Incremented counter to: %i\n--------------------\n\n", *file_input_counter_ptr);
    
    }
    fclose(file_pointer);
    
    
}

int decideOpImportance(char *op){
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
    file_pointer = fopen("jcpd.io", "w");
    char *current_op;
    char current_op_prec = 0;
    for(int index=0; index<*file_input_counter_ptr; index++){
        //printf("Index: %i\n", index);
        if(isOperatorI2P(file_inputs[index])){
            //printf("Looking at: %s\n", file_inputs[index]);
            if((*file_inputs[index] == '/') || (*file_inputs[index] == '*') || (*file_inputs[index] == '+') || (*file_inputs[index] == '-') || (*file_inputs[index] == '^') || (*file_inputs[index] == '%') || (*file_inputs[index] == '(') || (*file_inputs[index] == ')')){   
                
                if((*file_inputs[index] == '(') || (*file_inputs[index] == ')')){}
                
                else if((*stack_counter_ptr == 0) || (decideOpImportance(file_inputs[index]) > decideOpImportance(stack[*stack_counter_ptr-1]))){
                    //printf("current top of stack: %s\n", stack[*stack_counter_ptr-1]);
                    //printf("Current stack top's importance: %i\n", decideOpImportance(stack[*stack_counter_ptr-1]));
                    
                    strcpy(stack[*stack_counter_ptr], file_inputs[index]);
                    (*stack_counter_ptr)++;
                    //printf("%s added to stack\n", file_inputs[index]);
                    
                    current_op = file_inputs[index];
                    current_op_prec = decideOpImportance(file_inputs[index]);
                    //printf("new op: %s\n", file_inputs[index]);
                    //printf("new op importance: %i\n", current_op_prec);
                    //("new top of stack: %s\n", stack[*stack_counter_ptr-1]);
                    //printf("Importance of %s ", file_inputs[index]);
                    //printf("is %i\n", current_op_prec);
                    //printf("Writing %s\n", file_inputs[index]);
                    //fprintf(file_pointer, "%s\n", file_inputs[index]);
                }
                
                else{
                    (*stack_counter_ptr)--;
                    //printf("Else triggered by %s\n", stack[*stack_counter_ptr]);
                    while(decideOpImportance(file_inputs[index]) <= decideOpImportance(stack[*stack_counter_ptr])){
                        //printf("Else Writing %s\n", stack[*stack_counter_ptr]);
                        fprintf(file_pointer, "%s\n", stack[*stack_counter_ptr]);
                        (*stack_counter_ptr)--;
                        if(*stack_counter_ptr <= -1){
                            break;
                        }
                    }
                    (*stack_counter_ptr)++;
                    strcpy(stack[*stack_counter_ptr], file_inputs[index]);
                    (*stack_counter_ptr)++;
                    //printf("(else)new top of stack: %s\n", stack[*stack_counter_ptr-1]);
                }
            }
        }
        
        else{
            //printf("Writing %s\n", file_inputs[index]);
            fprintf(file_pointer, "%s\n", file_inputs[index]);
        }
    }
    (*stack_counter_ptr)--;
    while(*stack_counter_ptr >= 0){
        //printf("Stack item: %s\n", stack[*stack_counter_ptr]);
        fprintf(file_pointer, "%s\n", stack[*stack_counter_ptr]);
        (*stack_counter_ptr)--;
    }
    fclose(file_pointer);    
}





void infixToPostfix()
{
	char exp[20];
	char* e, x;
    char line[1000];
    FILE *file_pointer;
    int stack_counter = 0;
    int *stack_counter_ptr = &stack_counter;
    char stack[20][20];
    char file_inputs[100][100];
    int file_input_counter = 0;

    //printf("Enter the expression :");
    readFile(file_pointer, line, file_inputs, &file_input_counter);
    organiseStack(file_pointer, stack, stack_counter, stack_counter_ptr, file_inputs, &file_input_counter);
	
    /*    
	while (*e != '\0')
	{
		if (isalnum(*e) || *e == '.')
		{
            
			printf("%c", *e);
			//printf("\n");
		}
		else if (*e == '(')
			push(*e);
		else if (*e == ')')
		{
			while ((x = pop()) != '(')
				printf("%c", x);
				printf("\n");
		}
		else
		{
			while (priority(stack[top]) >= priority(*e))
				//printf("\n");
				printf("%c", pop());
				printf("\n");
			push(*e);
		}
		e++;
	}
	while (top != -1)
	{
		//printf("\n");
		printf("\n%c", pop());
	}
	// printf("\n");*/
}
