
//---------------------------------------------------------------
// File: expression.h
// Purpose: Header file for the Expression data structure
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
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
extern Exp* createExpNode();
extern void setSymbol(Exp*, char*);//Create a symbol node 
extern void setFirst(Exp*, Exp*);
extern void setRest(Exp*, Exp*);


#endif