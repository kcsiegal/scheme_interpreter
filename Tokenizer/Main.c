
#include <stdio.h>
#include <stdlib.h>
#include "TokenList.h"

int main(int argc, char *argv[]) {
    TokenList *tokens;
    char *expression = malloc(256 * sizeof(char));
    while (fgets(expression, 256, stdin)) {
        tokens = tokenize(expression);
        printTokens(tokens);
		ConsCell* popVal = NULL;
		//popVal = pop(tokens);
		//printf("%p", popVal);
		//printTokens(tokens);
    }
    free(expression);
    cleanup(tokens);
    free(tokens);
    return 1;

}

