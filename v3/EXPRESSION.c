//---------------------------------------------------------------
// File: expression.c
// Purpose: C file for the Expression data structure
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
//---------------------------------------------------------------
#include "EXPRESSION.h"

//--------------------------------------------
// Function: createExp()                                    
// Purpose: creates an expression node             
// Preconditions: None
// Returns: Exp*
//--------------------------------------------
Exp* createExpNode(){
	Exp* x = (Exp*)calloc(1,sizeof(Exp));
	return x;
}


//--------------------------------------------
// Function: setSymbol(char*)                                    
// Purpose: assigns the symbol to the exp              
// Preconditions: None
// Returns: void
//--------------------------------------------
void setSymbol(Exp* exp, char* x){
	//exp->symbol = (char*)calloc(2 * sizeof(x) * sizeof(Exp));
	exp->symbol = x;
}


//--------------------------------------------
// Function: void setFirst(Exp*, Exp*);                                    
// Purpose: Assigns a first to an Exp             
// Preconditions: None
// Returns: void
//--------------------------------------------
void setFirst(Exp* curr, Exp* first){
	curr->first = first;
}


//--------------------------------------------
// Function: void setRest(Exp*, Exp*);                                    
// Purpose: Assigns a rest to an Exp             
// Preconditions: None
// Returns: void
//--------------------------------------------
void setRest(Exp* curr, Exp* rest){
	curr->rest = rest;
}