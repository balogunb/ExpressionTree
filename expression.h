#ifndef EXPRESSION
#define EXPRESSION


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Exp {
	char* symbol;
	struct Exp* rest;
} Exp;


typedef struct ExpTree {
	struct Exp* root;
	int size;
} ExpTree;


extern Exp* createExp(char*);
extern ExpTree* createTree(char*);
extern void printExpression(ExpTree*);
extern void evaluate(ExpTree*);
extern void appendExpression(ExpTree*, char*);
extern void printSubset(char*);


#endif


