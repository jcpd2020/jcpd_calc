#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000
/*
Paul Gunnarsson
117430404
*/


/*
 * Takes in two pointers, each pointing to a string.
 * Joins the two strings together into one long string.
 * Returns a pointer to this new string.
 */
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


/*
 * Takes in a string, a string character pointer, the 2d token array, a pointer to different tokens within that array, and a small character array with room for only two characters.
 * This function saves the indexed character in the input string into a token slot in the 2d array. It will either write to a new token, or continue writing to the last token.
 * It returns nothing.
 */
void saveToken(int i, char str[MAXCHAR], char tokens[MAXCHAR][MAXCHAR], int *token_counter_ptr, char temp[2]){
    char *res;
    char *character1 = tokens[*token_counter_ptr];
    char *character2 = &(str[i]);
    strncpy(temp, character2, 1);
    res = concater(character1, &temp[0]);
    strcpy(tokens[*token_counter_ptr], res);
    free(res);
}


/*
 * Takes in a pointer to a character which might be an operator.
 * Determines if the character is an operator or an operand.
 * Returns a 1 if it is an operator, or a 0 if it is not.
 */
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

/*
 * Takes in a file pointer, a token counter for indexing the 2d token array and the 2d array of tokens.
 * It will write each token to a new line in the file
 * It will return nothing.
 */
void writeToFile(FILE *file_pointer, int token_counter, char tokens[MAXCHAR][MAXCHAR]){
    file_pointer = fopen("jcpd.io", "w");
    int i = 0;
    for(i=0; i<=token_counter;i++){
        fprintf(file_pointer, "%s\n", tokens[i]);
    }
    fclose(file_pointer);
}

/*
 * Takes in the 2d array of tokens which the tokeniser will work with
 * It will read in the file, seperating each token into a new line
 * It will return the number of tokens in the array
 */
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
            
            else if(isdigit(str[i]) || str[i] == '.'){
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
        
    }
	token_counter--;
	fclose(file_pointer);
    return token_counter;
}

/*
 * It takes in the interface file name
 * It runs the tokeniser and then writes each token to a new line
 * It returns nothing
 */
void runTokeniser(char * filename) {
    char tokens[MAXCHAR][MAXCHAR];
    int token_count = tokenise(tokens);
    FILE *file_pointer = fopen(filename, "w");
    writeToFile(file_pointer, token_count, tokens);
    fclose(file_pointer);
}
