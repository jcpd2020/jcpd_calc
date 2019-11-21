#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000

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

void saveToken(int i, char str[MAXCHAR], char tokens[MAXCHAR][MAXCHAR], int *token_counter_ptr, char temp[2]){
    printf("In save token method. token_counter: %i\n", *token_counter_ptr);
    char *res;
    char *character1 = tokens[*token_counter_ptr];
    char *character2 = &(str[i]);
    strncpy(temp, character2, 1);
    res = concater(character1, &temp[0]);
    strcpy(tokens[*token_counter_ptr], res);
    free(res);
    printf("Exiting save token method\n");
}

//checks if the given string pointer points to an operator
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

int writeToFile(FILE *file_pointer, int token_counter, char tokens[MAXCHAR][MAXCHAR]){
    file_pointer = fopen("useroutput.txt", "w");
    int i = 0;
    printf("I'm about to write %i lines...\n\n", token_counter+1);
    for(i=0; i<=token_counter;i++){
        fprintf(file_pointer, "%s\n", tokens[i]);
    }
    fclose(file_pointer);
    free(file_pointer);
    
}

int tokenise(char tokens[MAXCHAR][MAXCHAR]){
    //char tokens[MAXCHAR][MAXCHAR];
    char temp[2];
    int token_counter = 0;
    FILE *file_pointer = fopen("userinput.txt", "r");
    char str[MAXCHAR];
	int str_length;
    int make_new_token_flag = 0;
    int writing_negative_number = 0;

    if (file_pointer != NULL){
		fgets(str, sizeof str, file_pointer);
		str_length = strlen(str);
        printf("String length: %i\n\n", str_length);

        for(int i = 0; i<str_length-1;i++){
            if((str[i] == '-' && token_counter == 0) || (str[i] == '-' && isOperator(tokens[token_counter-1]) == 1)){
                saveToken(i, str, tokens, &token_counter, temp);
                token_counter++;
                writing_negative_number = 1;
            }

            else if(isdigit(str[i])){
                printf("digit found\n");
                if(token_counter == 0){
                    printf("First token, be careful\n");
                }
                else if(writing_negative_number == 1 || !(isOperator(tokens[token_counter-1]))){
                    token_counter--;
                }
                
                printf("Saving digit. tc: %i\n", token_counter);
                saveToken(i, str, tokens, &token_counter, temp);
                token_counter++;
                writing_negative_number = 0;
            }

            else if (str[i] != ' ' && !(isalpha(str[i]))){
                printf("op found");
                saveToken(i, str, tokens, &token_counter, temp);
                token_counter++;
                writing_negative_number = 0;
            }

        }

        printf("\nToken list:\n-------------------\n");
        char *token_pointer;        
        for(int j = 0; j <= token_counter-1; j++){
            token_pointer = &(*tokens[j]);
            printf("Token: %s\n", tokens[j]);

        }

	}
	token_counter--;
	fclose(file_pointer);
    writeToFile(file_pointer, token_counter, tokens);
    
    
    return 0;
}
