#include "expression.h"


Exp* createExp(char* x){
	size = strlen(x);
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
		printExpHelper1(head, printVal);
		strcat(printVal,")");
	}
	printf("%s\n",printVal);
}


void printExpHelper1(Exp* curr,char * values ){
	if (curr == 0) return;


	//if its deepest node
	if (curr->first == 0 && curr->rest == 0){
		strcat(values,curr->symbol);
		return;
	}

	//if node is an expression;
	if (curr->first != 0 && curr->first->first != 0){
		strcat(values,"(");
		printExpHelper1(curr->first,values);
		strcat(values,")");
		if(curr->rest){
			strcat(values," ");
			printExpHelper1(curr->rest,values);
		}
		
		return;
	}

	//if node is the inner part of an expression
	if(curr->first != 0 && curr->first->symbol != 0){
		printExpHelper1(curr->first,values);

		//if it had other values
		if(curr->rest != 0){
			strcat(values," ");
			printExpHelper1(curr->rest,values);
		}
	}
}








//void evaluate(ExpTree*);
//void appendExpression(ExpTree*, char*);
//void printSubset(char*);