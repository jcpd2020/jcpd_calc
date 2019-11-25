/* author: David Ryan-Lynch, 115310721 */

#ifndef _VM_H
#define _VM_H

#include <math.h>
#include <string.h>
#include "stack.h"

void do_add();
void do_subtract();
void do_multiply();
void do_divide();
void do_modulus();
void do_exponential();

void grab_opcode(const char * line, char * opcode);
void grab_number(const char * line, float * number);
void do_instruction(const char * line);
int calculate();

#endif // _VM_H
