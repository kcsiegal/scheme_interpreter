
#include <stdio.h>
#include <stdlib.h>
#include "TokenList.h"
#include "Parser.h"


int main(int argc, char *argv[]) {
	TokenList *tokens;
	TokenList *parseTree;
	TokenList *leftoverTokens;
	
	
	int depth = 0;
	char *expression = malloc(256 * sizeof(char));
	
	while (fgets(expression, 256, stdin)) {
		
	tokens = tokenize(expression);
	/*if (!tokens) {
	    printf("Gets here");
	    continue;
	}*/
		
	append(leftoverTokens, tokens); 
	
	parseTree = parse(tokens,&depth);    // My parse() takes a list of tokens and an integer pointer, and 
	// returns a parse tree (a list) and changes depth to be the 
	// number of unclosed parens encountered while parsing tokens. 
		
	if (depth < 0) {
		printf("syntax error\n");   // Too many close parentheses. 
		return 0;
	} else if (depth > 0) {
		// There are more open parens than close parens, so these tokens are saved as leftovers.
		reverse(parseTree);
		leftoverTokens = parseTree;
		depth = 0;
	} else {
		while (!isEmptyPair(parseTree)) {
			printTree(car(parseTree));
			parseTree = cdr(parseTree);
		}
		leftoverTokens = NULL;
	}
	}
	
	
    printf("\n");
	if (!isEmptyPair(leftoverTokens)) {
		printf("syntax error\n");   //Too few close parens at end of input. 
		return 0;
	}
	
	

}


