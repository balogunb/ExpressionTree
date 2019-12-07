//---------------------------------------------------------------
// File: EXPRESSIONUTILS.c
// Purpose: C file for the Expression's utilities'
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
//---------------------------------------------------------------
#include "EXPRESSIONUTILS.h"




//--------------------------------------------
// Function: createExp(char*)                                    
// Purpose: Creates and expression from the given
// 			string input               
// Preconditions: None
// Returns: A pointer to the created struct Expression
//--------------------------------------------
Exp* createExp(char* x){
	// printf("-createExp- %s\n",x);
	// printf("%d\n", strlen(x));
	size = size + strlen(x);//holds length of the expression string
	Exp* exp = createExpNode();

	//if input is an expression
	if(x[0] == '('){
		createExpHelper2(exp,x);
	}
	else{//if its just an element by itself
		setSymbol(exp,x);
	}
	return exp;
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
	// printf("-createExpHelper- [%s]\n",x);
	// printf("%d\n", strlen(x));
	if(strlen(x) == 0)return;

	

	//if first operand is in the
	//form "(<operator> <space separated list of operands>)"
	if(x[0] == '('){ 
		int newLength = strlen(x);
		char* front = (char*)malloc(newLength*sizeof(char));
		char* back = (char*)malloc(newLength*sizeof(char));
		Exp* first = createExpNode();
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
		setFirst(exp,first);
		//recursively handle the form 
		//"(<operator> <space separated list of operands>)"
		createExpHelper2(first,front);


		//if there is/are operand(s) after inner expression
		if(x[++index] != 0){
			Exp* rest = (Exp*)calloc(1,sizeof(Exp));
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



	// printf("-createExpHelperInner- [%s]\n",pntr);
	// printf("%d\n", strlen(pntr));



	exp->symbol = malloc((strlen(pntr)+1) *sizeof(char));
	strcpy(exp->symbol,pntr);//append first number to first->symbol

	int length = strlen(pntr);
	if(strlen(x) != length){//if expression contains more than one expression
		char* pntrN = (char*)malloc(strlen(x) * sizeof(char));
		for(int i = 0; i < strlen(x);i++){
			pntrN[i] = x[i + length +1];
		}
		Exp* rest = (Exp*)calloc(1,sizeof(Exp));;
		exp->rest = rest;
		createExpHelper(rest,pntrN);
	}
}


//--------------------------------------------
// Function: createExpHelper2(Exp*,char*)                                    
// Purpose: Helper for function createExp              
// Preconditions: Takes in an Expression of 
// 			      form "(<operator> <space separated list of operands>)"
// Returns: void
//--------------------------------------------
void createExpHelper2(Exp* exp,char* x){
	// printf("-createExpHelper2- [%s]\n",x);
	// printf("%ld\n", strlen(x));

	int newLength = strlen(x) - 1;
	char* z = (char*)malloc(newLength*sizeof(char));
	

	//Handles operetor 
	char* sym = malloc(2 * sizeof(char));
	sym[0] = x[1];
	sym[1] = 0;
	setSymbol(exp,sym);//set operator to first
	

	//Concat the remainder of the expression to z
	for(int i = 3; i < newLength;i++){
	 	z[i-3] = x[i];	
	}
	z[newLength] = 0;//terminate z
	

	//Handles rest
	Exp* newRest = createExpNode();
	setRest(exp, newRest);
	//printf("%s\n",z);
	createExpHelper(newRest,z);//recursively handle rest
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
	free(printVal);
}



//--------------------------------------------
// Function: printExpHelper(Exp* curr,char * values)                                    
// Purpose: Helper method form print expression             
// Preconditions: None
// Returns: void
//--------------------------------------------
void printExpHelper(Exp* curr,char * values ){
	if (curr->symbol == 0 && curr->first == 0) return;


	//if its an expression containin a symbol
	if (curr->symbol){
		strcat(values,curr->symbol);
	}

	//if node is an expression of 
	// form "(<operator> <space separated list of operands>)"
	if (curr->first != 0){
		strcat(values,"(");
		printExpHelper(curr->first,values);//recursively call helper methods 
		strcat(values,")");
	}

	//if it has a rest
	if (curr->rest != 0){
		strcat(values," ");
		printExpHelper(curr->rest, values);
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
			printf("%ld\n",evaluateExp(curr));
	} 
}

//--------------------------------------------
// Function: evaluateExp(Exp* curr)                                    
// Purpose: Evaluates an expression of
//			form  "(<operator> <space separated list of operands>)"         
// Preconditions: None
// Returns: long int
//--------------------------------------------
long int evaluateExp(Exp* curr){
	char* symb = (char*)malloc(10 * sizeof(char));//holds operation
	strcpy(symb, curr->symbol);
	long int val = 0;

	//handles cases based on operation
		if (strcmp(symb, "+") == 0){
				val = evaluateFirst(curr->rest);//evaluates first item after operator
				if(curr->rest->rest){
						return val + evaluateHelper(curr->rest->rest, symb);
				}
    	}
    	else if(strcmp(symb, "-") == 0){
			if(curr->rest){
				val = evaluateFirst(curr->rest);
				if(curr->rest->rest){
						return val - evaluateHelper(curr->rest->rest, symb);
				}
			}
		}
		else if(strcmp(symb,"*") == 0){
			if(curr->rest){
				val = evaluateFirst(curr->rest);

				if(curr->rest->rest){
						return val * evaluateHelper(curr->rest->rest, symb);
				}
			}
		}
		return val;//if it gets here there is only one exp after the operator
}



//--------------------------------------------
// Function: evaluateFirst(Exp* curr)                                    
// Purpose: Evaluates an of one Exp*      
// Preconditions: None
// Returns: long int
//--------------------------------------------
long int evaluateFirst(Exp* curr){
	if(curr->first) return evaluateExp(curr->first);
	else{
			return atol(curr->symbol);
		}
}


//--------------------------------------------
// Function: evaluateHelper(Exp* curr,char *symb)                                   
// Purpose: helper method for evaluate          
// Preconditions: None
// Returns: long int value of the evaluated exp
//--------------------------------------------
long int evaluateHelper(Exp* curr,char *symb){

	//if Expression has an inner expression of type "(<operator> <space separated list of operands>)" 
	if(curr->first){
		if(!curr->rest){
			return evaluateExp(curr->first);
		}
		else{//if first has a rest

			if (strcmp(symb, "+") == 0){
					return evaluateExp(curr->first) + evaluateHelper(curr->rest,symb);
	    	}

	    	else if(strcmp(symb,"-") == 0){
				return evaluateExp(curr->first) + evaluateHelper(curr->rest,symb);
			}
			
			else if(strcmp(symb,"*") == 0){
				return evaluateExp(curr->first) * evaluateHelper(curr->rest,symb);
			}
		}
	} 

	else{
		//handles cases based on operation
		if (strcmp(symb, "+") == 0){
			if(!curr->rest) return evaluateFirst(curr);

			else{
				return evaluateFirst(curr) + evaluateHelper(curr->rest,symb);
			}
			
    	}

    	else if(strcmp(symb,"-") == 0){
			if(!curr->rest) return evaluateFirst(curr);

			else{
				return evaluateFirst(curr) + evaluateHelper(curr->rest,symb);
			}
		}
		
		else if(strcmp(symb,"*") == 0){
			if(!curr->rest) return evaluateFirst(curr);

			else{
				return evaluateFirst(curr) * evaluateHelper(curr->rest,symb);
			}
		}
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
void appendExpression(Exp* exp, char* c){
	Exp* pntr = exp;
	//look through until the last Exp
	//set pntr to last Exp
	char* k = (char*)malloc((strlen(c)+ 1)*sizeof(char));
	strcpy(k,c);

	while(pntr->rest != 0){
		pntr = pntr->rest; 
	}

	//create new rest
	pntr->rest = (Exp*)calloc(1,sizeof(Exp));
	Exp* newExp = createExp(k);	
	//pntr->rest->first = 0;

	//if char* to append is an expression 
	if(c[0] == '('){//Strip parentenses 
		pntr->rest->first = (Exp*)calloc(1,sizeof(Exp));
		pntr->rest->first = newExp;

	}

	else{//if it a lone integer
		pntr->rest = newExp;
	}
	printExpression(exp);
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
				if(pntr->symbol != 0){
					printf("%s\n",pntr->symbol );
					return;
				}
			}
			pntr = pntr->first;
		}

		//if 'r' go to rest
		if(s[i]  == 'r'){
			if(pntr->rest == 0){
				return;
			}
			pntr = pntr->rest;
		}
	}


	//if result is an inner expression
	if (pntr->symbol != 0){
		char sym = (pntr->symbol)[0];
		if (sym == '+' || sym == '-' || sym == '*'){
			printExpression(pntr);
			return;
		}
	}

	char *check = (char*)malloc(size * sizeof(char));
	printExpHelper(pntr, check);
	printf("%s\n",check);
	free(check);
}