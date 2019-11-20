#ifndef TOKENISER_H
#define TOKENISER_H

char *concater(char *str1, char *str2);

void saveToken(int i, char *str,  int token_counter);

int isOperator(char *maybe_op);

int writeToFile(int token_counter);

char tokenise();




#endif
