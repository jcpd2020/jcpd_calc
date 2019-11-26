/*
    Name:   Jack Curtin
    Student ID: 117359191
*/

#ifndef I2P_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define I2P_H
int isOperatorI2P(char *maybe_op);
void writeFile(FILE *file_pointer, char file_inputs[100][100], int *file_input_counter_ptr);
void readFile(FILE *file_pointer, char line[1000], char file_inputs[100][100], int *file_input_counter_ptr);
int decideOpImportance(char *op);
void organiseStack(FILE *file_pointer, char stack[20][20], int *stack_counter_ptr, char file_inputs[100][100], int *file_input_counter_ptr);
void infixToPostfix();
#endif
