#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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
      int operand;
      int operator;


      char first_char = line[0];

      char test_for_minus=first_char - '0';

      if(isdigit(*line) || (test_for_minus==-3 && strlen(line)>1)){
          bool floatTest= false;

          for (int count=0;count<25; count++){
              if (line[count]=='.'){
                  //then lf and break
                  fprintf(output_file, "lf %s", line);
                  floatTest=true;
                  break;
              }
          }
          if(floatTest==false){
            fprintf(output_file, "li %s", line);
          }
      }else{  //do case switching for each operator
          operator=first_char - '0';
          switch(operator){
            case -5:
              fprintf(output_file, "ad\n");
              break;
            case -3:
              fprintf(output_file, "su\n");
              break;
            case -6:
              fprintf(output_file, "mu\n");
              break;
            case -1:
              fprintf(output_file, "dv\n");
              break;
            case 46:
              fprintf(output_file, "pw\n");
              break;
            case -11:
              fprintf(output_file, "md\n");
              break;
            default:
              fprintf(output_file, "Error: operator not recognised\n");
          }
    }
  }

    fclose(input_file);
    fclose(output_file);
    remove(input);



    int ret = rename(output, input);

    return 0;
}
