//---------------------------------------------------------------
// File: expression.c
// Purpose: C file for the Expression data structure
// Programming Language: C
// Author: Basit Balogun
//---------------------------------------------------------------
#include "expression.h"

//--------------------------------------------
// Function: createExp(char*)                                    
// Purpose: Creates and expression from the given
// 			string input               
// Preconditions: None
// Returns: A pointer to the created struct Expression
//--------------------------------------------
Exp* createExp(char* x){
	size = size + strlen(x);//holds length of the expression string
	Exp* exp = (Exp*)malloc(sizeof(Exp));

	//if input is an expression
	if(x[0] == '('){
		createExpHelper2(exp,x);
	}
	else{//if its just an element by itself
		exp->symbol = x;
	}
	return exp;
}

//--------------------------------------------
// Function: createExpHelper2(Exp*,char*)                                    
// Purpose: Helper for function createExp              
// Preconditions: Takes in an Expression of 
// 			      form "(<operator> <space separated list of operands>)"
// Returns: void
//--------------------------------------------
void createExpHelper2(Exp* rest,char* x){
	int newLength = strlen(x) - 1;
	char* z = (char*)malloc(newLength*sizeof(char));
	
	
	Exp* first = (Exp*)malloc(sizeof(Exp));
	first->symbol = malloc(2 * sizeof(char));
	(first->symbol)[0] = x[1];//set operator to first
	

	//Add concat the remainder of the expression to z
	for(int i = 3; i < newLength;i++){
	 	z[i-3] = x[i];	
	}
	z[newLength] = 0;//terminate z
	

	//Handles rest
	Exp* newRest = (Exp*)malloc(sizeof(Exp));
	rest->first = first;
	rest->rest = newRest;
	createExpHelper(newRest,z);//recursively handle rest
}

//--------------------------------------------
// Function: createExpHelper(Exp*,char*)                                    
// Purpose: Helper for function createExp              
// Preconditions: Takes in an Expression of 
// 				  form "<space separated list of operands" or
// 				  form " operand"
// Returns: void
//--------------------------------------------
void createExpHelper(Exp* exp,char* x){	
	if(strlen(x) == 0)return;

	//if last operand append to first
	if(strlen(x) == 1){
		Exp* first = (Exp*)malloc(sizeof(Exp));
		first->symbol = malloc((strlen(x)+1) *sizeof(char));
		strcpy(first->symbol,x);
		exp->first = first;
		return;
	}

	//if first operand is in the
	//form "(<operator> <space separated list of operands>)"
	if(x[0] == '('){ 
		int newLength = strlen(x);
		char* front = (char*)malloc(newLength*sizeof(char));
		char* back = (char*)malloc(newLength*sizeof(char));
		Exp* first = (Exp*)malloc(sizeof(Exp));
		int index = 0;//
		int count = 0;//keeps track of closing parentenses

		//appends an inner expression to front
		while(1){
			front[index] = x[index];
			if(x[index] == '(') count++;
			if(x[index] == ')')	count--;
			if(count == 0) break;
			index++;
		}
		exp->first = first;
		//recursively handle the form 
		//"(<operator> <space separated list of operands>)"
		createExpHelper2(first,front);


		//if there is/are operand(s) after inner expression
		if(x[++index] != 0){
			Exp* rest = (Exp*)malloc(sizeof(Exp));
			++index; //adjust index based of index of the first
			int j = 0;
			while(index < strlen(x)){//append remaining characters to rest
				back[j++] = x[index++];
			}
			exp->rest = rest;
			createExpHelper(rest,back);//recusively handle rest
		}
		return;
	}

	//if it gets here the first thing is a number
	char array[strlen(x) + 1];
	strcpy(array,x);
	char *pntr = strtok(array," ");//concat string before first to pntr

	Exp* first = (Exp*)malloc(sizeof(Exp));
	first->symbol = malloc((strlen(pntr)+1) *sizeof(char));
	strcpy(first->symbol,pntr);//append first number to first->symbol
	exp->first = first;


	int length = strlen(pntr);
	if(strlen(x) != length){//if expression contains for than one expression
		char* pntrN = (char*)malloc(strlen(x) * sizeof(char));
		for(int i = 0; i < strlen(x);i++){
			pntrN[i] = x[i + length +1];
		}
		Exp* rest = (Exp*)malloc(sizeof(Exp));
		exp->rest = rest;
		createExpHelper(rest,pntrN);
	}
}

//--------------------------------------------
// Function: printExpression(Exp* head)                                    
// Purpose: prints the Expression             
// Preconditions: None
// Returns: void
//--------------------------------------------
void printExpression(Exp* head){
	//If Exp is empty
	if(head == NULL){
		printf("Expression has not been initialized");
		return;
	} 

	//holds the string expression
	char* printVal = (char*)malloc(size * sizeof(char));


	//if expression only has a number
	if(head->rest == 0){
		strcat(printVal,head->symbol);
	}
	else{
		strcat(printVal,"(");
		printExpHelper(head, printVal);
		strcat(printVal,")");
	}
	printf("%s\n",printVal);
}

//--------------------------------------------
// Function: printExpHelper(Exp* curr,char * values)                                    
// Purpose: Helper method form print expression             
// Preconditions: None
// Returns: void
//--------------------------------------------
void printExpHelper(Exp* curr,char * values ){
	if (curr == 0) return;


	//if its an expression containin a symbol
	if (curr->first == 0 && curr->rest == 0){
		strcat(values,curr->symbol);
		return;
	}

	//if node is an expression of 
	// form "(<operator> <space separated list of operands>)"
	if (curr->first != 0 && curr->first->first != 0){


		//handles inner expression of form form "(<operator> <space separated list of operands>)"
		strcat(values,"(");
		printExpHelper(curr->first,values);//recursively call helper methods 
		strcat(values,")");


		//handles case where expression has a rest
		if(curr->rest){
			strcat(values," ");
			printExpHelper(curr->rest,values);
		}
		return;
	}

	//if node is an expression of 
	// form "(<space separated list of operand(s)>)"
	if(curr->first != 0 && curr->first->symbol != 0){
		printExpHelper(curr->first,values);

		//if expression has more than one operand
		if(curr->rest != 0){
			strcat(values," ");
			printExpHelper(curr->rest,values);
		}
	}
}

//--------------------------------------------
// Function: evaluate(Exp* curr)                                    
// Purpose: prints the evaluated value of the 
//			expression            
// Preconditions: None
// Returns: void
//--------------------------------------------
void evaluate(Exp* curr){
	//If Exp is empty
	if(curr == NULL){
		printf("Expression has not been initialized");
		return;
	} 

	//if expression is one number
	if(curr->rest == 0){
		printf("%ld\n", atol(curr->symbol));
	}
	else{//if expression of form "(<operator> <space separated list of operands>)"
		char* symb = (char*)malloc(10 * sizeof(char));//holds operation
		strcpy(symb, curr->first->symbol);

		//handles cases based on operation
		if (strcmp(symb, "+") == 0){
			printf("%ld\n",evaluateHelper(curr->rest,&symb));
    	}
    	else if(strcmp(symb, "-") == 0){
			printf("%ld\n", evaluateHelper(curr->rest,&symb));
		}
		else if(strcmp(symb,"*") == 0){
			printf("%ld\n",evaluateHelper(curr->rest,&symb));
		}
	} 
}

//--------------------------------------------
// Function: evaluate(Exp* curr,char **op)
//			 op holds the address of the last operation                                    
// Purpose: helper method for evaluate          
// Preconditions: None
// Returns: long int value of the evaluated exp
//--------------------------------------------
long int evaluateHelper(Exp* curr,char **op){

	//if its an Exp* with a symbol
	if (curr->first == 0 && curr->rest == 0){
		char* sym = curr->symbol;
		//check if operand is a not a symbol
		if(strcmp(sym, "+") != 0 && strcmp(sym, "-") != 0 && strcmp(sym, "*") != 0){
			return atol(curr->symbol);//returns number
		}
	}

	//if node is an expression;
	if (curr->first != 0 && curr->first->first != 0){

		//set *op to the current operand
		free(*op);
		*op = (char*)malloc(10 * sizeof(char));
		strcpy(*op, curr->first->first->symbol);

		//if expression has a rest
		if(curr->rest){
			//Handles cases based on opertion
			if (strcmp(*op, "+") == 0){
				return evaluateHelper(curr->first,op) + evaluateHelper(curr->rest,op);
    		}
    		else if(strcmp(*op, "-") == 0){
				return evaluateHelper(curr->first,op) - evaluateHelper(curr->rest,op);
			}
			else if(strcmp(*op,"*") == 0){
				return evaluateHelper(curr->first,op) * evaluateHelper(curr->rest,op);
			}
		}
		
		//if expression does not have a rest simply return 
		return evaluateHelper(curr->first,op);
	}

	//if Expression does not start with an operation
	if(curr->first != 0 && curr->first->symbol != 0){

		//if it has a rest
		if(curr->rest != 0){
			if (strcmp(*op, "+") == 0){
				return evaluateHelper(curr->first,op) + evaluateHelper(curr->rest,op);
    		}
    		else if(strcmp(*op, "-") == 0){
				return evaluateHelper(curr->first,op) - evaluateHelper(curr->rest,op);
			}
			else if(strcmp(*op,"*") == 0){
				return evaluateHelper(curr->first,op) * evaluateHelper(curr->rest,op);
			}
		}		

		//if it does not have a rest
		else return evaluateHelper(curr->first,op);
	}
}	


//--------------------------------------------
// Function: appendExpression(Exp** exp,char *c)
//			 takes in address of previous expression
//			 char* of expression to be appended                                   
// Purpose: appends new char* to previously existing Expression         
// Preconditions: None
// Returns: void
//--------------------------------------------
void appendExpression(Exp** exp, char* c){
	Exp* pntr = *exp;

	//look through until the last Exp
	//set pntr to last Exp
	while(pntr->rest != 0){
		pntr = pntr->rest; 
	}


	//if char* to append is an expression 
	if(c[0] == '('){

		//if lone operand and lone number
		// ie "(+ 4)" , "(- 7)" ,"(* 15)"
		Exp* newExp = createExp(c);
		if(newExp->rest->rest == 0){
			pntr->rest = (Exp*)malloc(sizeof(Exp));
			pntr->rest->first = (Exp*)malloc(sizeof(Exp));
			pntr->rest->first->first = (Exp*)malloc(sizeof(Exp));
			pntr->rest->first->first->symbol = (char*)malloc(3* sizeof(char));
			pntr->rest->first->rest = (Exp*)malloc(sizeof(Exp));
			pntr->rest->first->rest->first = (Exp*)malloc(sizeof(Exp));
			pntr->rest->first->rest->first->symbol = (char*)malloc(50* sizeof(char));
			strcpy(pntr->rest->first->first->symbol,newExp->first->symbol);
			strcpy(pntr->rest->first->rest->first->symbol,newExp->rest->first->symbol);
		}
		else{
			pntr->rest = (Exp*)malloc(sizeof(Exp));
			pntr->rest->first = (Exp*)malloc(sizeof(Exp));
			pntr->rest->first = createExp(c);
		}

		
	}

	else{//if it a lone integer
		pntr->rest = (Exp*)malloc(sizeof(Exp));
		pntr->rest = createExp(c);
	}
	printExpression(*exp);
}


//--------------------------------------------
// Function: printSubset(Exp* exp,char *s)
//			 takes in address of anexpression
//			 char* to decide what subset to print                                  
// Purpose:  print a subset of the Exp    
// Preconditions: char* must be a valid position in the Exp
// Returns: void
//--------------------------------------------
void printSubset(Exp* exp, char* s){
	Exp* pntr = exp;


	//goes through the list of characters
	for(int i = 0; i < strlen(s);i = i+2){


		//if 'f' go to first
		if(s[i]  == 'f'){
			if(pntr->first == 0){
				printf("invalid Expression\n");
				return;
			}
			pntr = pntr->first;
		}

		//if 'r' go to rest
		if(s[i]  == 'r'){
			if(pntr->rest == 0){
				printf("invalid Expression\n");
				return;
			}
			pntr = pntr->rest;
		}
	}

	//if its a number print the number
	if(pntr->symbol != 0){
		printf("%s\n",pntr->symbol );
		return;
	}
	char *check = (char*)malloc(size * sizeof(char));
	//if its an expression use print helper to print the expression
	if(pntr->first->symbol == 0){
		printExpHelper(pntr,check);
		printf("%s\n",check );
		return;
	}


	strcpy(check,pntr->first->symbol);

	//if it is pointing to an Exp whose first's symbol is not an expression
	if(strcmp(check, "+") != 0 && strcmp(check, "-") != 0 && strcmp(check, "*") != 0){
		printf("invalid Expression\n");
		return;
	}

	printExpression(pntr);//if it gets here it is an expression
}