#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    //File names assigned for reuse
    char input[]="input.txt";
    char output[]="output.txt";

    FILE * input_file;
    FILE * output_file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    input_file = fopen(input, "r");
    output_file = fopen(output, "a");
    if (input_file == NULL){
        return 0;
    }

    while ((read = getline(&line, &len, input_file)) != -1) {
        //Your code here - "line" is variable name

    }

    fclose(input_file);
    fclose(output_file);
    remove(input);



    int ret = rename(output, input);

    return 0;
}
