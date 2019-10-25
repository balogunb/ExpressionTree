#include "expression.h"


Exp* createExp(char* x){
	size = strlen(x);
	printf("Initial\n");
	printf("%s\n",x);

	Exp* exp = (Exp*)malloc(sizeof(Exp));
	if(x[0] == '('){
		createExpHelper2(exp,x);
	}
	else createExpHelper(exp,x);
	return exp;
}

void createExpHelper2(Exp* rest,char* x){

	printf("got the 21\n");
	printf("%s\n",x);

	int newLength = strlen(x) - 1;
	char* z = (char*)malloc(newLength*sizeof(char));
	//char symbol = x[1];
	//add all char of subexpression to a new char*
	for(int i = 3; i < newLength;i++){
		z[i-3] = x[i];	
	}
	Exp* first = (Exp*)malloc(sizeof(Exp));
	Exp* newRest = (Exp*)malloc(sizeof(Exp));
	first->symbol = malloc(2 * sizeof(char));
	(first->symbol)[0] = x[1];
	printf("got the 22\n");
	printf("%s\n",z );
	rest->first = first;
	rest->rest = newRest;
	createExpHelper(newRest,z);	
}



void createExpHelper(Exp* exp,char* x){
	

	if(strlen(x) == 0)return;
	//if no more characters left return
	// if(x[0] == ')'){
	// 	return;
	// } 

	printf("got the 11\n");
	printf("%s\n",x);

	//if only one character left and not back space 
	//int currLength = strlen(x);
	if(strlen(x) == 1){
		printf("got the 12\n");
		exp->symbol = x;
		printf("%s\n",exp->symbol );
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
			// first->symbol = malloc(2 * sizeof(char));
			// (first->symbol)[0] = x[1];
			// printf("got the 2\n");
			// printf("%s\n",first->symbol );
			// exp->first = first;
			// exp->rest = rest;
			// createExpHelper2(first,y);//apppends only items in parenthenses
			// createExpHelper(rest,y);//work on rest 
			// return;
	}

	//if it gets here the first thing is a number 

	//char temp = x[0];
	// int newLength = strlen(x) - 1;
	// char* z = (char*)malloc(newLength*sizeof(char));

	// //add all char of subexpression to a new char*
	// for(int i = 2; i < strlen(x);i++){
	// 	z[i-2] = x[i];	
	// }

	// Exp* first = (Exp*)malloc(sizeof(Exp));
	// Exp* rest = (Exp*)malloc(sizeof(Exp));
	// first->symbol = malloc(2 * sizeof(char));
	// (first->symbol)[0] = x[0];
	// exp->first = first;
	// exp->rest = rest;
	// createExpHelper(rest,z);
}


void printExpression(Exp* head){

	//If Exp is empty
	if(head == NULL){
		printf("Expression has not been initialized");
		return;
	} 


	char* printVal = (char*)malloc(size * sizeof(char));
	printExpHelper(head, printVal);

	printf("%s\n",printVal);

}


void printExpHelper(Exp* curr,char * values ){
	if (curr == NULL) return;


	if(curr->first == 0 && curr->rest == 0){
		strcat(values,curr->symbol);
		return;
	}



	if(curr->first != NULL){
		printExpHelper(curr->first, values);
	}

	if(curr->rest != NULL){
		printExpHelper(curr->first, values);
	}
}
//void evaluate(ExpTree*);
//void appendExpression(ExpTree*, char*);
//void printSubset(char*);