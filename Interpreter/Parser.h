/*
 Parser.h
 By Group Swiss
 For CS 251 - A header file for Parser.c including the structs used within. 
 */

#include <stdio.h>
#include <stdlib.h>
//#include "TokenList.h"


TokenList* parse(TokenList* tokens, int* depth);


int isEmptyPair(TokenList* parseTree);


void printValue(ConsCell* value);


ConsCell* car(TokenList* parseTree);


TokenList* cdr(TokenList* parseTree);


void printTree(ConsCell* tree);