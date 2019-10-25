#ifndef EXPRESSION
#define EXPRESSION


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Exp {
	char* symbol;
	struct Exp* first;
	struct Exp* rest;
} Exp;


// typedef struct ExpTree {
// 	struct Exp* root;
// } ExpTree;


int size;
//bool firstCase;
extern Exp* createExp(char*);
//extern Exp* createTree(char*);
void createExpHelper(Exp*,char* );
void createExpHelper2(Exp*,char*);
extern void printExpression(Exp*);
void printExpHelper(Exp* head,char * values );
extern void evaluate(Exp*);
extern void appendExpression(Exp*, char*);
extern void printSubset(char*);


#endif


