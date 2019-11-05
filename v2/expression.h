
//---------------------------------------------------------------
// File: expression.h
// Purpose: Header file for the Expression data structure
// Programming Language: C
// Author: Basit Balogun
//---------------------------------------------------------------
#ifndef EXPRESSION
#define EXPRESSION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Structure Definition for Expression
// Structure format: 
//	An Exp struct with a symbol cannot have a first
//	An Exp with a first cannot have a symbol
// 	Either of the expressions above can have a rest
typedef struct Exp {
	char* symbol;//Holds operational symbol or number
	struct Exp* first;
	struct Exp* rest;
} Exp;


int size;//holds the number of character in the expression

//Functions
extern Exp* createExp(char*);//create the expression
void createExpHelper(Exp*,char* );
void createExpHelper2(Exp*,char*);
extern void printExpression(Exp*);
void printExpHelper(Exp*,char *);
extern void evaluate(Exp*);
long int evaluateHelper(Exp*,char**);
extern void appendExpression(Exp**, char*);
extern void printSubset(Exp*, char*);//prints subset using combinations of 'r' and 'f'



#endif