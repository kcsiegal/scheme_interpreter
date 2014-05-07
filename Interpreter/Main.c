#include <stdio.h>
#include <stdlib.h>
#include "TokenList.h"
#include "Parser.h"
#include "Interpreter.h"


void main() {
    Binding* bindingtest1 = malloc(sizeof(Binding));
    bindingtest1->name = "test";
    bindingtest1->type = 3;
    
    Binding* bindingtest2 = malloc(sizeof(Binding));
    bindingtest2->name = "test";
    bindingtest2->type = 3;
    
    Binding* bindingtest3 = malloc(sizeof(Binding));
    bindingtest3->name = "test";
    bindingtest3->type = 3;
    
    char* tester = "Does this work?";
    bindingtest1->pointer = tester;
    
    Environment* environment = malloc(sizeof(Environment));
    add(environment->bindings, bindingType, bindingtest1);
    add(environment->bindings, bindingType, bindingtest2);
    add(environment->bindings, bindingType, bindingtest3);
    
    

}