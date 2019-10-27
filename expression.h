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


int size;
extern Exp* createExp(char*);
void createExpHelper(Exp*,char* );
void createExpHelper2(Exp*,char*);
extern void printExpression(Exp*);
void printExpHelper(Exp*,char *);
extern void evaluate(Exp*);
long int evaluateHelper(Exp*,char**);
extern void appendExpression(Exp**, char*);
extern void printSubset(Exp*, char*);


#endif


