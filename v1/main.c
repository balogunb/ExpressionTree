//---------------------------------------------------------------
// File: main.c
// Purpose: Allow different functions to be made on Expressions 
//			based on terminal input
// Programming Language: C
// Author: Basit Balogun
// 
// Commands:
// ’c’: create a new expression. The next line contains the expression. A new data structure is
// created and the current expression will point to it.
// • ’p’: print the current expression
// • ’e’: evaluate the current expression (arithmetically)
// • ’a’: append a new expression to the current expression. The new expression is given on the
// 		  next line
// 		  Assuming the current expression is: ”(+ 1 2 3)”.
// 		  Appending ”4” would result in ”(+ 1 2 3 4)”, while appending ”(+ 4)” would result in ”(+ 1
// 		  2 3 (+ 4))”
// • ’s’: prints a subset of the expression. The subset specification is on the next line and uses ’f’
//		  (first) and ’r’ (rest)
// • "Print": terminates the program
//---------------------------------------------------------------
#include "expression.h"


int main(){
	Exp* head = (Exp*) malloc(sizeof(Exp));

	printf("%s\n","Insert command or type \"Exit\" to exit " );
	char x[7];
	fgets(x,7,stdin);//takes in the command
	x[strcspn(x, "\n")] = 0;//removes \n from end of x 

	//Exit terminates the program
	while(strcmp(x,"Exit" ) != 0){

		//Handles create
		if(strcmp(x, "c") == 0){
			free(head);
			char expression[300];
			fgets(expression,300,stdin);
			expression[strcspn(expression, "\n")] = 0;
			head = createExp(expression);
			//free(expression);
			
		}

		//Handles print
		else if(strcmp(x,"p") == 0){
			printExpression(head);
			
		}

		//Handles Append
		else if(strcmp(x,"a") == 0){
			char appendStr[300];
			fgets(appendStr,300,stdin);
			appendStr[strcspn(appendStr, "\n")] = 0;
			appendExpression(&head,appendStr);
			//free(appendStr);
		}

		//Handles subset
		else if(strcmp(x, "s") == 0){
			char subset[300];
			fgets(subset,300,stdin);
			subset[strcspn(subset, "\n")] = 0;
			printSubset(head,subset);
			//free(subset);
		}
		else if(strcmp(x, "e") == 0){
			evaluate(head);
		}
		fgets(x,7,stdin);
		x[strcspn(x, "\n")] = 0;
	}
	//free(x);
	return 0;	
}