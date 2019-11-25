/*
    Author: Cristian Gaudino
    ID: 117434292
*/
#ifndef CODE_GEN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CODE_GEN_H


int isNumber(char *line, char temp[2]);

int isFloat(char *line);

char * operatorSwitching(char *first_char);

int generate_code(char * filename);

#endif
