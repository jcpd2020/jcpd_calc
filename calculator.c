#include "tokeniser.h"
#define MAXCHAR 1000


int main(){
    char tokens[MAXCHAR][MAXCHAR];
    int token_count = tokenise(tokens);
    FILE *file_pointer = fopen("jcpd.io", "w");
    writeToFile(file_pointer, token_count, tokens);
}
