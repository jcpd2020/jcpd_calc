#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000
/*
Paul Gunnarsson
117430404
*/


//Take in pointers to two strings, join the strings together and return a pointer to the result 
char *concater(char *str1, char *str2){
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
}

//Take in the input string character pointer, the string, the 2d token array, the pointer to the token counter and a character array that can only store 2 characters. It will save the character in the string (indexed by i) to the appropriate token slot in the 2d array.
void saveToken(int i, char str[MAXCHAR], char tokens[MAXCHAR][MAXCHAR], int *token_counter_ptr, char temp[2]){
    char *res;
    char *character1 = tokens[*token_counter_ptr];
    char *character2 = &(str[i]);
    strncpy(temp, character2, 1);
    res = concater(character1, &temp[0]);
    strcpy(tokens[*token_counter_ptr], res);
    free(res);
}

//Checks if the given string pointer points to an operator. Returns a 1 if it's an operator, or a 0 if it's an operand.
int isOperator(char *maybe_op){
    char op = *maybe_op;
    char op_temp[2];
    char *op_temp_pointer = op_temp;

    strncpy(op_temp, maybe_op, 2);

    if((*(op_temp_pointer+1) == '\0') && ((*op_temp_pointer == '-') || (*op_temp_pointer == '+') || (*op_temp_pointer == '^') || (*op_temp_pointer == '/') || (*op_temp_pointer == '*') || (*op_temp_pointer == '%') || (*op_temp_pointer == '(') || (*op_temp_pointer == ')'))){
        return 1;
    }

    return 0;
}

//Take in a 2d array and the amount of tokens, then put each token on its own line.
void writeToFile(FILE *file_pointer, int token_counter, char tokens[MAXCHAR][MAXCHAR]){
    file_pointer = fopen("jcpd.io", "w");
    int i = 0;
    for(i=0; i<=token_counter;i++){
        fprintf(file_pointer, "%s\n", tokens[i]);
    }
    fclose(file_pointer);
    free(file_pointer);
    
}

//Take in a 2d array to store the tokens, then reads the jcpd.io file to split the user input up into tokens, saving them into the array. Once done, it returns the token counter, which will have recorded the number of tokens in the array.
int tokenise(char tokens[MAXCHAR][MAXCHAR]){
    char temp[2];
    int token_counter = 0;
    FILE *file_pointer = fopen("jcpd.io", "r");
    char str[MAXCHAR];
	int str_length;
    int make_new_token_flag = 0;
    int writing_negative_number = 0;

    if (file_pointer != NULL){
		fgets(str, sizeof str, file_pointer);
		str_length = strlen(str);
        for(int i = 0; i<str_length-1;i++){
            if((str[i] == '-' && token_counter == 0) || (str[i] == '-' && isOperator(tokens[token_counter-1]) == 1)){
                saveToken(i, str, tokens, &token_counter, temp);
                token_counter++;
                writing_negative_number = 1;
            }

            else if(isdigit(str[i])){
                if(token_counter == 0){}
                else if(writing_negative_number == 1 || !(isOperator(tokens[token_counter-1]))){
                    token_counter--;
                }
                
                saveToken(i, str, tokens, &token_counter, temp);
                token_counter++;
                writing_negative_number = 0;
            }

            else if (str[i] != ' ' && !(isalpha(str[i]))){
                saveToken(i, str, tokens, &token_counter, temp);
                token_counter++;
                writing_negative_number = 0;
            }

        }
        
        //For debugging purposes. Prints out the list of tokens in the 2d array.
        /*printf("\nToken list:\n-------------------\n");
        char *token_pointer;        
        for(int j = 0; j <= token_counter-1; j++){
            token_pointer = &(*tokens[j]);
            printf("Token: %s\n", tokens[j]);

        }*/

	}
	token_counter--;
	fclose(file_pointer);
    return token_counter;
}
