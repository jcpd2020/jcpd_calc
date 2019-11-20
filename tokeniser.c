#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000

char tokens[MAXCHAR][MAXCHAR];
FILE *file_pointer;
int token_counter = 0;
char temp[2];
char *temp_pointer = temp;
    

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

void saveToken(int i, char *str){
    char *res;
    char *character1 = &(*tokens[token_counter]);
    char *character2 = &(str[i]);
    strncpy(temp, character2, 1);
    res = concater(character1, temp_pointer);
    strcpy(tokens[token_counter], res);
    free(res);
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

int writeToFile(){
    file_pointer = fopen("useroutput.txt", "w");
    int i = 0;
    printf("About to write %i lines...\n\n", token_counter+1);
    for(i=0; i<=token_counter;i++){
        fprintf(file_pointer, "%s\n", tokens[i]);
    }
    
    
}

int tokenise(){
    char str[MAXCHAR];
    int str_length;
    int make_new_token_flag = 0;
    token_counter = 0;
    int writing_negative_number = 0;
    file_pointer = fopen("userinput.txt", "r");
    
    if (file_pointer != NULL){
		fgets(str, sizeof str, file_pointer);
		str_length = strlen(str);
                        
        for(int i = 0; i<str_length-1;i++){
            if((str[i] == '-' && token_counter == 0) || (str[i] == '-' && isOperator(tokens[token_counter]) == 1)){
                if(token_counter != 0){
                    token_counter++;
                }
                printf("\n\nfirst line: %s\n", tokens[token_counter-2]);
                saveToken(i, (char *)str);
                make_new_token_flag = 0;
                writing_negative_number = 1;
            }
            
            else if(isdigit(str[i]) || str[i] == '.'){
                if(make_new_token_flag == 1 && writing_negative_number !=1){
                    token_counter ++;
                    make_new_token_flag = 0;
                }
                saveToken(i, (char *)str);                
            }
            
            else if (str[i] != ' ' && !(isalpha(str[i]))){
                token_counter++;
                saveToken(i, (char *)str);
                make_new_token_flag = 1;
                writing_negative_number = 0;
            }
            
        }
        
        printf("\nToken list:\n-------------------\n");
        char *token_pointer;        
        for(int j = 0; j <= token_counter; j++){
            token_pointer = &(*tokens[j]);
            printf("Token: %s\n", tokens[j]);
            
        }
                
	}
	fclose(file_pointer);
    free(file_pointer);
    return 0;
}



