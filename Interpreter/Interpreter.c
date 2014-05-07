#include <stdio.h>
#include <stdlib.h>
#include "TokenList.h"
#include "Parser.h"

ConsCell* load(char* filename, Environment* parent) {
	Closure loadClosure = malloc(sizeof(Closure));
}