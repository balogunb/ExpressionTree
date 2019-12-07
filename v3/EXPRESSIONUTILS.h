//---------------------------------------------------------------
// File: EXPRESSIONUTILS.h
// Purpose: Header file for the Expression's utilites
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
//---------------------------------------------------------------

#ifndef EXPRESSIONUTILS
#define EXPRESSIONUTILS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "EXPRESSION.h"


//Utilities and their helper functions 
extern Exp* createExp(char*);//create the expression
void createExpHelper(Exp*,char* );
void createExpHelper2(Exp*,char*);
extern void printExpression(Exp*);
extern void evaluate(Exp*);
long int evaluateHelper(Exp*,char*);
long int evaluateExp(Exp*);
long int evaluateFirst(Exp*);
extern void appendExpression(Exp*, char*);
extern void printSubset(Exp*, char*);//prints subset using combinations of 'r' and 'f'
void printExpHelper(Exp*,char *);

//Write recursive free if time permits



#endif