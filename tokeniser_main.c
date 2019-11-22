#include "tokeniser.h"
#define MAXCHAR 1000


int main(){
    char tokens[MAXCHAR][MAXCHAR];
    int token_count = tokenise(tokens);
    FILE *file_pointer = fopen("useroutput.txt", "w");
    writeToFile(file_pointer, token_count, tokens);
    //char *token_ptr = token; 
    //printf("\n\nMain has retreived: %s", token_pointer);
    
    //writeToFile(tokens);
}
