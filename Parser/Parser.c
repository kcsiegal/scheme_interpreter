/*
 cs251-f11-swiss
 Parser.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "TokenList.h"
#include "Parser.h"



TokenList* parse(TokenList* tokens, int* depth) {
	
	TokenList* parseStack = malloc(sizeof(TokenList));
	
	while (!(isEmptyPair(tokens))) {
		if (car(tokens)->car->type != 6) {
		    if(car(tokens)->car->type == 5) {
                (*depth)= (*depth) + 1;
			}
			push(parseStack, pop(tokens));
		}
		else {
			(*depth) = (*depth) - 1;
			push(parseStack, pop(tokens));
			TokenList* tempStack = malloc(sizeof(TokenList));
			while (car(parseStack) && (car(parseStack)->car->type != 5)) {
				push(tempStack, pop(parseStack));
			}
			
			if (car(parseStack)) {
				push(tempStack, pop(parseStack));
			}
			ConsCell* treeCell= malloc(sizeof(ConsCell));
			
			Value* token = (Value*)malloc(sizeof(Value));
			ValueInit(token, branchType, tempStack->head);
			Value* next = (Value*)malloc(sizeof(Value));
			ValueInit(next, cdrType, NULL);
			treeCell->car = token;
			treeCell->cdr = next; 
			
			push(parseStack, treeCell);
		}
		
	}
	
	return parseStack;
}


int isEmptyPair(TokenList* parseTree) {
	if(parseTree)
		return !(parseTree->head);
	else {
		return 1;
	}
	
}

void printValue(ConsCell* value) {
	int type = value->car->type;
	
	if (type == 0) {
		if (value->car->boolValue == 0) {
			printf("#f ");
		}		
		else{
			printf("#t ");
		}
	}	
	else if (type == 1) {
		printf("%d ", value->car->intValue);
	}
	
	else if (type == 2) {
		printf("%f ", value->car->fltValue);
	}
	
	else if (type == 3) {
		printf("%s ", value->car->strValue);
	}
	else if (type == 4) {
		printf("%s ", value->car->symbValue);
	}
	else if (type == 5) {
		printf("%c", value->car->open);
	}
	else if (type == 6) {
		printf("%c", value->car->close);
	}
}

ConsCell* car(TokenList* parseTree) {
	return parseTree->head;
}

TokenList* cdr(TokenList* parseTree) {
	TokenList* cdrList = malloc(sizeof(TokenList));
	cdrList->head = parseTree->head->cdr->cdr;
	return(cdrList);
	
}

void printTree(ConsCell* tree) {
	if (tree->car->type == branchType) {
		printTree(tree->car->branch);
	}
	else {
		printValue(tree);
	}
	if (tree->cdr->cdr) {
		printTree(tree->cdr->cdr);
	}
}