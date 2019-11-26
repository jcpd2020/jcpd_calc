#include <ctap.h>
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokeniser.h"
#include "i2p.h"
#include "code_gen.h"
#include "vm.h"
#include "stack.h"*/
#include "calculator.h"

#define MAXCHAR 1000

TESTS {

    plan(1);

    // full integration test - assumes no knowledge, black box
    char *filename = "jcpd.io";
    char *line = (char*) malloc(256);
    FILE *file_pointer = fopen("jcpd.io", "w");  // write test equation
    fprintf(file_pointer, "%s", "32 * 9 + .6 - -10.8 / 2 ^ 2 % 2"); 
    fclose(file_pointer);
    runCalculator();
    file_pointer = fopen("jcpd.io", "r");  // read calculated answer
    fgets(line, MAXCHAR, file_pointer);
    fclose(file_pointer);
    is(line, "-2.400001", "Compare the result of the calculation to what it should be. 32 * 9 + .6 - 10.8 / 2 ^ 2 % 2 = -2.4 (plus floating point rounding error)");
}
