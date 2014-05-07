#include <stdio.h>
#include <stdlib.h>


struct __Binding {
	char* name;
	int type;
	int* pointer;
};
typedef struct __Binding Binding;

struct __Environment {
    TokenList* bindings;
	int* parent;
    };
typedef struct __Environment Environment;

struct __Closure {
	TokenList* parameters;
    TokenList* schemeCode;
    Environment* environment;
    };
typedef struct __Closure Closure;
    
