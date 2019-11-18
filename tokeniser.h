#ifndef __TOKENISER__H
#define __TOKENISER__H

char *concater(char *str1, char *str2);

int isOperator(char *maybe_op);

int tokenise();

int writeToFile();

int main();

void saveToken();

#endif
