/*
 TokenList.h
 By Group Swiss
 For CS 251 - A header file for TokenList.c including the structs used within. 
 */

#include <stdio.h>
#include <stdlib.h>

/*
 Just a simple enum to make for easier reference to the different data types later on.
 */

enum TOKEN_TYPE {
	booleanType, integerType, floatType, stringType, symbType, openType, closeType, cdrType, branchType, bindingType
};

/*
 The lowest level of the data structure. Either contains a data type or a pointer to the next node of the Linked List.
 */

struct __Value {
	int type;
	union {
		int boolValue;
		int intValue;
		double fltValue;
		char* strValue;
		char* symbValue;
		char open;
		char close;
		struct __ConsCell* cdr;
		struct __ConsCell* branch;
		struct __Binding* binding;
	};
};

typedef struct __Value Value;

/*
 Constructor for Value structure. Pass in the type of data (or if it's a pointer) and a pointer to the data it contains.
 */

void ValueInit(Value* value, int type, void* data);

/*
 Next level for the data structure. Node for the linked list. 
 The first value (car) is a data type, second value (cdr) is a pointer 
 */

struct __ConsCell{
	Value* car;
	Value* cdr;
};

typedef struct __ConsCell ConsCell;

/*
 Main Linked List structure. Simply contains pointer to head ConsCell.
 */

struct __TokenList{
	ConsCell* head;
};

typedef struct __TokenList TokenList;

/* 
 Creates a new ConsCell containing the passed data (of passed type) in it's car and whose cdr points to the old front of the list.
 Places that new ConsCell at the head of the TokenList. 
 */

void add(TokenList* tokens, int type, void* data);

/*
 Not yet implemented.
 */

void reverse(TokenList* tokens);

/*
 Prints each token from the Scheme code and it's type in the format "<token> : <type>"
 */

void printTokens(TokenList* tokens);

/*
 Cleans up memory allocated to the Heap.
 */

void cleanup(TokenList* tokens);

/*
 Makes a TokenList for the passed line of scheme code.
 */

ConsCell* pop(TokenList* tokens);

void push(TokenList* tokens, ConsCell* cell);

void deleteFirst(TokenList* tokens);

void append(TokenList* extraTokens, TokenList* tokens);


TokenList* tokenize(char* line);
