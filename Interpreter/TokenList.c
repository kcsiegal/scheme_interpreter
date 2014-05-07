/*
 cs251-f11-swiss
 TokenList.c
 Last updated : 10/18/11 20:55
 */

#include <stdio.h>
#include <stdlib.h>
#include "TokenList.h"

void ValueInit(Value* value, int type, void* data) {
	
	value->type = type;
	
	if (type == booleanType) {
		value->boolValue = *(int*)data;
	}
	else if (type == integerType) {
		value->intValue = *(int*)data;
	}
	else if (type == floatType) {
		value->fltValue = *(double*)data;
	}
	else if (type == stringType) {
		value->strValue = (char*)data;
	}
	else if (type == symbType) {
		value->symbValue = (char*)data;
	}
	else if (type == openType) {
		value->open = *(char*)data;
	}
	else if (type == closeType) {
		value->close = *(char*)data;
	}
	else if (type == cdrType) {
		value->cdr = (ConsCell*)data;
	}
	else if (type == branchType) {
		value->branch = (ConsCell*)data;
	}
}

void add(TokenList* tokens, int type, void* data) {
	Value* token = (Value*)malloc(sizeof(Value));
	ValueInit(token, type, data);
	ConsCell* new = (ConsCell*)malloc(sizeof(ConsCell));
	Value* next = (Value*)malloc(sizeof(Value));
	
	if (tokens->head == NULL) {
		ValueInit(next, cdrType, tokens->head);
		tokens->head = new;
		new->car = token;
		new->cdr = next;
	}
	else {
		ValueInit(next, cdrType, tokens->head);
		new->car = token;
		new->cdr = next;
		tokens->head = new;
	}
}

void printTokens(TokenList* tokens) {

    if(tokens) {
        
        ConsCell* current = tokens->head;
        
        while (current != NULL) {
        
            
            if (current->car->type == booleanType) {
                printf ("%d : boolean \n", current->car->boolValue);
                current = current->cdr->cdr;
            }	  
            
            else if (current->car->type == integerType) {
                printf ("%d : integer \n", current->car->intValue);
                current = current->cdr->cdr;
                
            }
            else if (current->car->type == floatType) {
                printf ("%f : float \n", current->car->fltValue);
                current = current->cdr->cdr;
                
            }
            else if (current->car->type == stringType) {
                printf ("%s : string \n", current->car->strValue);
                current = current->cdr->cdr;
                
            }
            else if (current->car->type == symbType) {
                printf ("%s : symbol \n", current->car->symbValue);
                current = current->cdr->cdr;
                
            }
            else if (current->car->type == openType) {
                printf ("%c : open \n", current->car->open);
                current = current->cdr->cdr;
                
            }
            else if (current->car->type == closeType) {
                printf ("%c : close \n", current->car->close);
                current = current->cdr->cdr;
                
            }
            
        }
    }
}

void deleteFirst(TokenList* tokens) {
	if (tokens->head) {
		ConsCell* temp = tokens->head->cdr->cdr; 
		tokens->head = temp;
	}
}

ConsCell* pop(TokenList* tokens){
	ConsCell* temp;
	if (tokens->head){
		temp = tokens->head;
		deleteFirst(tokens);
	}
	return temp;
}

void push(TokenList* tokens, ConsCell* cell){
	cell->cdr->cdr = tokens->head;
	tokens->head = cell;
}

void append(TokenList* extraTokens, TokenList* tokens) {
	if (extraTokens)
	{
		reverse(extraTokens);
		while(extraTokens->head) {
			ConsCell* temp;
			temp = pop(extraTokens);
			push(tokens, temp);
		}
		free(extraTokens);
	}
}

void reverse(TokenList* tokens){
	if (isEmptyPair(tokens)) {
		return;
	}
	ConsCell* current = tokens->head;
	ConsCell* previous = NULL;
	ConsCell* next = current->cdr->cdr;
	while (next != NULL) {
		current->cdr->cdr = previous;
		previous = current;
		current = next;
		next = current->cdr->cdr;
	}
	current->cdr->cdr = previous;
	tokens->head = current;
}

void cleanup(TokenList* tokens) {
	ConsCell* current = tokens->head;
	ConsCell* next = current->cdr->cdr;
	while (next != NULL) {
		tokens->head = next;
		free(current->car);
		free(current->cdr);
		free(current);
		current = next;
		next = current->cdr->cdr;
	}
	free(current->car);
	free(current->cdr);
	free(current);
}

TokenList* tokenize(char* line) {
	
	TokenList* tokens = malloc(sizeof(TokenList));
	
	//Set up a counter for the placement in an input line
	int i = 0;
	char c = line[i];
	//Until end of line is reached
	while (c != '\0' && c != '\n') {
		//Increment on white space
		if (c == ' ') {
			c = line[++i];
		}
		
		//Check for open paren
		if (c == '(') {
			add(tokens, 5, &c);
			c = line[++i];
			continue;
			
		}
		
		//Check for close paren
		if (c == ')') {
			add(tokens, 6, &c);
			c = line[++i];
			continue;
		}
		
		//Check for comment
		if (c == ';') {
			break;
		}
		
		//Check for a string
		if (c=='\"') {
			char* textString = malloc(255);
			int j = 0;
			textString[j++] = c;
			c = line[++i];
			while (c != '\"' && c != '\0') {
				textString[j++] = c;
				c = line[++i];
			}
			textString[j++] = c;
			c = line[++i];
			add(tokens, 3, textString);
		}
		
		
		//Check for a number
		if (c >= '0' && c <= '9' || ((c == '+' || c == '-') && (line[i + 1] > '0' && line[i+1] < '9'))){	
			char* intString = malloc(255);
			int j = 0;
			//Start with integer set to true
			int integer = 1;
			intString[j++] = c;
			c = line[++i];
			while (c >= '0' && c <= '9') {
				intString[j++] = c;
				c = line[++i];
			}
			if (c == '.') {
				//Number has a decimal; integer is set to false
				integer = 0;
				intString[j++] = c;
				c = line[++i];
				while (c >= '0' && c <= '9') {
					intString[j++] = c;
					c = line[++i];
				}
			}
			//Number ended without encountering non-numeric characters	
			if (c == ' ' || c == '\0' || c == '(' || c == ')') {
				int intNum;
				double floatNum;
				if (integer) {
					intNum = atoi(intString);
					add(tokens, 1, &intNum);
				}
				else {
					floatNum = atof(intString);
					add(tokens, 2, &floatNum);
				}
				
			}
			
			//Non-numeric characters were encountered; token is stored as symbol
			else{
				while (c != ' ' && c != '\0' && c != '(' && c != ')' && c!=';') {
					intString[j++] = c;
					c = line[++i];
				}
				add(tokens, 4, intString);
				if (c == ';') {
					break; 
				}
				
			}
		}
		
		//Check for a symbol
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c=='*'|| c=='/'|| c=='>'|| c=='<'|| c=='=' || c == '+' || c == '-'){
			char* symbolString = malloc(255);
			int j = 0;
			while (c != ' ' && c != '\0' && c != '(' && c != ')' && c!=';') {
				symbolString[j++] = c;
				c = line[++i];
			}
			
			add(tokens, 4, symbolString);
			if (c == ';') {
				break; 
			}
		}
		
		//Check for a quote symbol
		if (c=='\'') {
			add(tokens, 4, "'");
			c = line[++i];
		}
		
		//Check for a boolean
		if (c == '#') {
			c = line[++i];
			if (c == 't') {
				int x = 1;
				add(tokens, 0, &x);
				c = line[++i];
			}
			else if (c == 'f') {
				int x = 0;
				add(tokens, 0, &x);
				c = line[++i];
			}
			//'#' did not start boolean; token is stored as symbol
			else {
				add(tokens, 4, "#");
			}
		}
		
		
		
		
		
		
		
	}
	reverse(tokens);
	return tokens;
	
}





