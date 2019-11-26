#ifndef TOKENISER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TOKENISER_H

//Paul Gunnarsson
//117430404

char *concater(char *str1, char *str2);

void saveToken(int i, char str[1000], char tokens[1000][1000], int *token_counter_ptr, char temp[2]);

int isOperator(char *maybe_op);

void writeToFile(FILE *file_pointer, int token_counter, char tokens[1000][1000]);

int tokenise(char tokens[1000][1000]);

void runTokeniser(char * filename);


#endif
