#include "tokeniser.h"
#include "i2p.h"
#include "code_gen.h"
#include "stack.h"
#include "vm.h"
#define MAXCHAR 1000


int runCalculator(){
    char * filename = "jcpd.io";
    
    runTokeniser(filename);
    
    infixToPostfix();
    
    generate_code(filename);
    
    calculate();
    
    return 0;
    
}
