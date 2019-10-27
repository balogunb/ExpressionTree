#include "expression.h"


Exp* createExp(char* x){
	size = size + strlen(x);
	printf("Initial\n");
	printf("%s\n",x);
	Exp* exp = (Exp*)malloc(sizeof(Exp));

	if(x[0] == '('){//If it has an operator 
		createExpHelper2(exp,x);
	}
	else{//if its just an element by itself
		exp->symbol = x;
	}
	return exp;
}

void createExpHelper2(Exp* rest,char* x){

	printf("got the 21\n");
	printf("%s\n",x);

	int newLength = strlen(x) - 1;
	char* z = (char*)malloc(newLength*sizeof(char));
	//char symbol = x[1];
	//add all char of subexpression to a new char*
	Exp* first = (Exp*)malloc(sizeof(Exp));
	first->symbol = malloc(2 * sizeof(char));
	(first->symbol)[0] = x[1];
	
	 for(int i = 3; i < newLength;i++){
	 	z[i-3] = x[i];	

	 }
	 z[newLength] = 0;//terminate z


	printf("Special%c\n",z[0]);

	
	Exp* newRest = (Exp*)malloc(sizeof(Exp));
	printf("got the 22\n");
	printf("%s\n",z );
	rest->first = first;
	rest->rest = newRest;
	createExpHelper(newRest,z);	
}

void createExpHelper(Exp* exp,char* x){	
	if(strlen(x) == 0)return;

	printf("got the 11\n");
	printf("%s\n",x);

	//if only one character left and not back space 
	//int currLength = strlen(x);
	if(strlen(x) == 1){
		printf("got the 12\n");
		Exp* first = (Exp*)malloc(sizeof(Exp));
		//first->symbol = x;
		first->symbol = malloc((strlen(x)+1) *sizeof(char));
		strcpy(first->symbol,x);
		exp->first = first;
		printf("%s\n",first->symbol );
		return;
	}

	//if subexpression
	//Try just taking the last element away more efficient 
	if(x[0] == '('){
		printf("got the 13\n");
		printf("%s\n",x);
		
		//firstCase = !firstCase;//now false 
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
		printf("got the 14\n");
		printf("%s\n",front);

		exp->first = first;
		createExpHelper2(first,front);

		if(x[index + 1] == 0) printf("No val after exp\n");
		//if there are still values after the expression
		if(x[++index] != 0){//or if == ' ';
			Exp* rest = (Exp*)malloc(sizeof(Exp));
			++index; //go to the next possible express
			int j = 0;
			while(index < strlen(x)){
				back[j++] = x[index++];
			}
			exp->rest = rest;
			printf("got the 15\n");
			printf("%s\n",back);
			createExpHelper(rest,back);
		}
		return;
	}

	//if it gets here the first thing is a number
	char array[strlen(x) + 1];
	strcpy(array,x);
	char *pntr = strtok(array," ");
	printf("got the 41\n");
	printf("%s\n",x );

	Exp* first = (Exp*)malloc(sizeof(Exp));
	first->symbol = malloc((strlen(pntr)+1) *sizeof(char));
	//first->symbol = pntr;
	strcpy(first->symbol,pntr);
	exp->first = first;
	printf("Actual%s\n",first->symbol);


	int length = strlen(pntr);

	if(strlen(x) != length){
		char* pntrN = (char*)malloc(strlen(x) * sizeof(char));

		for(int i = 0; i < strlen(x);i++){
			pntrN[i] = x[i + length +1];
			printf("%c\n",x[i + length + 1]);
		}
		printf("got the 42\n");
		printf("%s\n",pntrN);
		Exp* rest = (Exp*)malloc(sizeof(Exp));
		exp->rest = rest;
		createExpHelper(rest,pntrN);
	}
	
}


void printExpression(Exp* head){
	//If Exp is empty
	if(head == NULL){
		printf("Expression has not been initialized");
		return;
	} 

	printf("Start Print\n");
	char* printVal = (char*)malloc(size * sizeof(char));

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


void printExpHelper(Exp* curr,char * values ){
	if (curr == 0) return;


	//if its deepest node
	if (curr->first == 0 && curr->rest == 0){
		strcat(values,curr->symbol);
		return;
	}

	//if node is an expression;
	if (curr->first != 0 && curr->first->first != 0){
		strcat(values,"(");
		printExpHelper(curr->first,values);
		strcat(values,")");
		if(curr->rest){
			strcat(values," ");
			printExpHelper(curr->rest,values);
		}
		
		return;
	}

	//if node is the inner part of an expression
	if(curr->first != 0 && curr->first->symbol != 0){
		printExpHelper(curr->first,values);

		//if it had other values
		if(curr->rest != 0){
			strcat(values," ");
			printExpHelper(curr->rest,values);
		}
	}
}


void evaluate(Exp* curr){
	//If Exp is empty
	if(curr == NULL){
		printf("Expression has not been initialized");
		return;
	} 

	printf("Start Evaluating\n");

	if(curr->rest == 0){
		printf("%ld\n", atol(curr->symbol));
	}
	else{
		char* symb = (char*)malloc(10 * sizeof(char));
				strcpy(symb, curr->first->symbol);
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

long int evaluateHelper(Exp* curr,char **op){
	//if (curr == 0) return;


	//if its deepest node
	if (curr->first == 0 && curr->rest == 0){
		//check if it is not an expression
			//printf("hmm%s\n",curr->symbol );
			//printf("hmm%s\n",*op );
			//printf("hmm22%s\n",*op );
			
			char* sym = curr->symbol;
			//printf("com%d\n", strcmp(*op, "x"));

		if(strcmp(sym, "+") != 0 && strcmp(sym, "-") != 0 && strcmp(sym, "*") != 0){
			//printf("hmm%s\n",curr->symbol );
			//printf("hmm%s\n",*op );
			return atol(curr->symbol);
		}
		
	}

	//if node is an expression;
	if (curr->first != 0 && curr->first->first != 0){
		//strcat(values,"(");
		free(*op);
		*op = (char*)malloc(10 * sizeof(char));
		strcpy(*op, curr->first->first->symbol);
		//printf("%s\n","got here" );
		//printf("%s\n",*op );


		//printf("1%s\n",curr->first->first->symbol );
		//printf("1%s\n",*op );
		//evaluateHelper(curr->first,op);

		//printExpHelper(curr->first,values);
		//strcat(values,")");
		if(curr->rest){
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
		
		return evaluateHelper(curr->first,op);//et here if there is no rest
	}

	//if node is the inner part of an expression
	if(curr->first != 0 && curr->first->symbol != 0){
		//return evaluateHelper(curr->first, op);
		//printf("%s\n","got here" );
		//printf("%s\n",*op );
		//printf("sym%s\n",curr->first->symbol );
		//char* symb = curr->first->symbol;
		//if it had other values
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
		else return evaluateHelper(curr->first,op);
	}
}	


	// //if its an inner expression
	// if(curr->first != 0 && curr->first->symbol != 0){
	// 	char* pntr = curr->first->symbol;
	// 	int boolean = 0;

	// 	//if it is an operand

	// 	if (strcmp(pntr, "+") == 0){
	// 		op = "+";
	// 		if(curr->rest->first->symbol != 0){
	// 			boolean = 1;
	// 			int nextInt = atol(curr->rest->first->symbol);
	// 			return(nextInt + evaluateHelper(curr->rest, op));
	// 		}
 //    	}
 //    	else if(strcmp(pntr, "-") == 0){
 //    		op = "-";
	// 		if(curr->rest->first->symbol != 0){
	// 			boolean =1;
	// 			int nextInt = atol(curr->rest->first->symbol);
	// 			return(nextInt - evaluateHelper(curr->rest, op));
	// 		}
 //    	}
 //    	else if(strcmp(pntr, "*") == 0){
 //    		op = "*";
 //    		if(curr->rest->first->symbol != 0){
 //    			boolean =1;
	// 			int nextInt = atol(curr->rest->first->symbol);
	// 			return(nextInt * evaluateHelper(curr->rest, op));
	// 		}
 //    	}
 //    	if(boolean == 0){//if it is not an operand 

 //    		//check if it has a rest
 //    		if(curr->rest != 0){

 //    			//if rest is a operation 
 //    			if(curr->rest->first->first != 0){
 //    				return evaluateHelper(curr->rest->first,"");
 //    			}

 //    			else{//if rest is a number
 //    				int nextInt1 = atol(curr->rest->first->symbol);
 //    				if (strcmp(op, "+") == 0){
	// 					return(nextInt1 + evaluateHelper(curr->rest, op));
 //    				}
 //    				else if(strcmp(pntr, "-") == 0){
	// 					return(nextInt1 - evaluateHelper(curr->rest, op));
 //    				}
 //    				else if(strcmp(pntr, "*") == 0){
	// 					return(nextInt1 * evaluateHelper(curr->rest, op));
 //    				}
 //    			}
 //    		}
	// 	}
	// }

void appendExpression(Exp** exp, char* c){
	Exp* pntr = *exp;
	while(pntr->rest != 0){
		pntr = pntr->rest; 
	}
	if(c[0] == '('){
	pntr->rest = (Exp*)malloc(sizeof(Exp));
	pntr->rest->first = (Exp*)malloc(sizeof(Exp));
	pntr->rest->first = createExp(c);
	}
	else{
		pntr->rest = (Exp*)malloc(sizeof(Exp));
		pntr->rest = createExp(c);
	}
}
void printSubset(Exp* exp, char* s){
	Exp* pntr = exp;
	for(int i = 0; i < strlen(s);i++){
		if(s[i]  == 'f'){
			if(pntr->first == 0){
				printf("invalid Expression\n");
				return;
			}
			pntr = pntr->first;
		}
		if(s[i]  == 'r'){
			if(pntr->rest == 0){
				printf("invalid Expression\n");
				return;
			}
			pntr = pntr->rest;
		}
	}
	printf("%s\n","printing subset" );
	if(pntr->symbol != 0){
		printf("%s\n",pntr->symbol );
		return;
	}
	char *check = (char*)malloc(size * sizeof(char));
	if(pntr->first->symbol == 0){
		printExpHelper(pntr,check);
		printf("%s\n",check );
		return;
	}


	strcpy(check,pntr->first->symbol);
	printf("%s\n",check );
	printf("%d\n",strcmp(check, "+") );


	//if it is pointing to a node whose first's symbol is not an expression
	if(strcmp(check, "+") == 1 && strcmp(check, "-") == 1 && strcmp(check, "*") == 1){
		printf("invalid Expression\n");
		return;
	}

	printExpression(pntr);//if it gets here it is an expression

	


}