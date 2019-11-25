#include "tokeniser.h"
#include "i2p.h"
#include "code_gen.h"
#include "stack.h"
#include "vm.h"
#define MAXCHAR 1000


int main(){
    //char filee[1000];
    char * filename = "jcpd.io";
    //FILE * file_pointer = NULL;
    
    //tokeniser
    do_the_thing(filename);
    /*file_pointer = fopen("jcpd.io", "r");
    while (fgets(filee, MAXCHAR, file_pointer)){
        //remove the newline character at the end of each line read from a file
        filee[strlen(filee)-1] = '\0';
        printf("After tokeniser\n--------------\n%s\n", filee);
    }
    fclose(file_pointer);*/
    
    
    //i2p
    infixToPostfix();
    /*file_pointer = fopen("jcpd.io", "r");
    while (fgets(filee, MAXCHAR, file_pointer)){
        //remove the newline character at the end of each line read from a file
        filee[strlen(filee)-1] = '\0';
        printf("After i2p\n--------------\n%s\n", filee);
    }
    fclose(file_pointer);*/
    
    //code gen
    generate_code(filename);
    /*file_pointer = fopen("jcpd.io", "r");
    while (fgets(filee, MAXCHAR, file_pointer)){
        //remove the newline character at the end of each line read from a file
        filee[strlen(filee)-1] = '\0';
        printf("After code_gen\n--------------\n%s\n", filee);
    }
    fclose(file_pointer);*/
    
    // vm
    calculate();
    /*file_pointer = fopen("jcpd.io", "r");
    while (fgets(filee, MAXCHAR, file_pointer)){
        //remove the newline character at the end of each line read from a file
        filee[strlen(filee)-1] = '\0';
        printf("After vm\n--------------\n%s\n", filee);
    }
    fclose(file_pointer);*/
    
    return 0;
    
}
