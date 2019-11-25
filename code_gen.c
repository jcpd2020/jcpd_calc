/*
    Author: Cristian Gaudino
    ID: 117434292
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int isNumber(char *line, char temp[2]){
    /*
    * Input: *line - Pointer to a character array; temp[2] - character array of size
    * Checks if given input is a number (integer or float)
    * Returns: numTest - 1 if number, else 0
    */
    int numTest=0;

    char test_for_minus= temp[0] - '0';   //temp[0] - '0'; will take the first character from temp and convert it to a number

    if(isdigit(*line) || (test_for_minus==-3 && strlen(line)>2)){ 
      /* 
      *  isdigit() returns true if the string is a number. However, this returns false for negative numbers, to account for this the first character of temp
      *  which was converted to a number is checked against -3 ("-" converts to -3). If the first character is a - and it is greater than length 2 (2 because of \n)
      */
      numTest = 1;
    }

    return numTest;
}

int isFloat(char *line){
    /*
    * Input: *line - pointer to a character array
    * Checks if given input is a float
    * Returns: floatTest - 1 if float, else 0
    */

    int floatTest=0;

    for (int count=0;count<25; count++){
        //Loop through the input checking for a "." character
        if (line[count]=='.'){
            floatTest=1;
            break;
        }
    }
    return floatTest;

}

char * operatorSwitching(char *first_char){
    /*
    * Input: *first_char - pointer to character array
    * Converts the given operand to assembly code through case switching
    * Returns: operator - pointer to a char array containing the assembly code
    */
    int intOperator=*first_char - '0';  //Converts the character to it's integer equivalent (Needed for case switching)
    char *operator;

    switch(intOperator){  //Using the resulting number, convert to assembly code
        case -5:
            operator="ad";
            break;
        case -3:
            operator="su";
            break;
        case -6:
            operator="mu";
            break;
        case -1:
            operator="dv";
            break;
        case 46:
            operator="ex";
            break;
        case -11:
            operator="md";
            break;
        default:
            operator="Error";
            break;
    }
    return operator;

}

int generate_code(char * filename){

    char * input =filename;
    char output[]="output.txt";

    FILE * input_file;
    FILE * output_file;
    char * line = NULL;
    size_t len = 0;
    size_t read;
    char temp[2]; //Empty character array to be used later

    input_file = fopen(input, "r");
    output_file = fopen(output, "a");
    if (input_file == NULL){
        return 0;
    }

    while ((read = getline(&line, &len, input_file)) != -1) {
        
        char *first_char = &(line[0]); //Take the first character from the line
        strncpy(temp, first_char, 1); // Copy the character to the empty array 
        temp[1] = '\0'; //Add the termination character to the array
        int numResult = isNumber(line, temp); //invoke numResult using the full line and the temp array

        if(numResult==1){
            int floatResult=isFloat(line);

            if(floatResult==1){
                fprintf(output_file, "lf %s", line);
            }else{
                fprintf(output_file, "li %s", line);
            }
        }else{
            char *opResult=operatorSwitching(first_char); //invoke switching and pass the first character of the line
            fprintf(output_file, "%s\n", opResult);
        }

    }
  
  fclose(input_file);
  fclose(output_file);
  remove(input);

  rename(output, input);  //Rename output, this results in the illusion that the same file is being used for input and output

  return 0;

}
