/* author: David Ryan-Lynch, 115310721 */

#include <math.h>  // for power and modulus functions
#include <string.h>  // for strlen() and strtod()
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define JCPD_FILENAME "jcpd.io"
#define MAXLINELENGTH 256

void do_add() {
    /* input: none
     * action: add top two items on stock
     * return: none */
    push(pop() + pop());  // position agnostic
}
void do_multiply() {
    /* input: none
     * action: multiply top two items on stock
     * return: none */
    push(pop() * pop());  // position agnostic
}
void do_subtract() {
    /* input: none
     * action: subtract top two items on stock
     * return: none */
    float a = pop();
    float b = pop();
    push(b - a);
}
void do_divide() {
    /* input: none
     * action: divide top two items on stock
     * return: none */
    float a = pop();
    float b = pop();
    push(b / a);
}
void do_exponential() {
    /* input: none
     * action: raise 2nd item from top to power of top
     * return: none */
    float a = pop();
    float b = pop();
    push(powf(b, a));
}
void do_modulus() {
    /* input: none
     * action: mod top two items on stock
     * return: none */
    float a = pop();
    float b = pop();
    push(fmodf(b, a));
}

void grab_opcode(const char * line, char * opcode) {
    /* input: line from file, ptr to place opcode in
     * action: place opcode from line into given opcode ptr
     * return: none */
    int i;
    for (i = 0; i < 2; i++) {
        opcode[i] = line[i];
    }
    opcode[i] = 0;  // terminate end
}

void grab_number(const char * line, float * number) {
    /* input: line from file, ptr to place number in
     * action: place number from line into given number ptr
     * return: none */
    char * buffer = (char *) malloc(33);  // max 32 bytes
    int linelen = (int) strlen(line);
    int i;

    // (i + 3) because the opcode and space take up 3 chars at the start of line
    for (i = 0; i + 3 < linelen; i++) {
        buffer[i] = line[i + 3];
    }
    buffer[i] = 0;  // terminate end

    // convert ascii number to corresponding int
    * number = (float) strtod(buffer, (char **)NULL);  // string -> double -> float
    free(buffer);
}

void do_instruction(const char * line) {
    /* input: line of instruction to execute
     * action: execute instruction
     * return: none */
    char * opcode = (char *) malloc(3);  // two digit opcode
    grab_opcode(line, opcode);
    if ((strncmp(opcode, "li", 2) == 0) || (strncmp(opcode, "lf", 2) == 0)) {  // load operator: just push number to stack
        float number;  // one variable for ints and floats, no point discerning between each
        grab_number(line, &number);
        push(number);
    } else {  // action operator: perform the operator with the operands on stack
        if (strncmp(opcode, "ad", 2) == 0) {  // ad = add
            do_add();
        } else if (strncmp(opcode, "su", 2) == 0) {  // su = subtract
            do_subtract();
        } else if (strncmp(opcode, "mu", 2) == 0) {  // mu = multiply
            do_multiply();
        } else if (strncmp(opcode, "dv", 2) == 0) {  // dv = divide
            do_divide();
        } else if (strncmp(opcode, "md", 2) == 0) {  // md = modulus
            do_modulus();
        } else if (strncmp(opcode, "ex", 2) == 0) {  // ex = exponential
            do_exponential();
        } else {  // unknown opcode!
            fputs("ERROR: unknown opcode, check input file for errors!\n", stderr);
        }
    }
    free(opcode);
}


int calculate() {
    FILE * fp = NULL;  // file pointer
    char * line = (char *) malloc(MAXLINELENGTH + 1);  // storage for next line, +1 for null terminator
    int returnval;

    fp = fopen(JCPD_FILENAME, "r");
    if (fp != NULL) {
        while (fgets(line, MAXLINELENGTH, fp) != NULL) {
            do_instruction(line);
        }
        float answer = pop();
        printf("Answer: %f\n", answer);
        fclose(fp);
        
        // write answer to file (for testing)
        fp = fopen(JCPD_FILENAME, "w");
        fprintf(fp, "%f", answer);
        fclose(fp);
        
        returnval = 0;
    } else {
        fputs("ERROR: file not found\n", stderr);
        returnval = 1;
    }
    free(line);
    //fclose(fp);
    return returnval;
}


