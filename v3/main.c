//---------------------------------------------------------------
// File: main.c
// Purpose: Allow different functions to be made on Expressions 
//			based on terminal input
// Programming Language: C
// Author: Basit Balogun
// Version: 3.0
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
#include "EXPRESSIONUTILS.h"




Exp* test(){

	//Test append single number -> 
	Exp* head = createExp("(+ 2 4 7)");
	printExpression(head);

	// appendExpression(head,"4");
	// appendExpression(head, "(- 4 4)");
	// appendExpression(head, "5");
	// appendExpression(head, "(- 4 5 (+ 2 3) (-5 6))");

	return head;
}

int main(){



	/*Test area starts            */
	//All expression functions work currectly 


	 // Exp* head = test();
	 // printExpression(head);
	 // printf("stopper\n");


	/*Test area ends           */
	

	







	///*

	

	Exp* head = createExpNode();
	printf("%s\n","Insert command or type \"Exit\" to exit " );
	char c = '0';//holds command
	char* cStr = (char*)malloc(100*sizeof(char));//String for create
	char* aStr = (char*)malloc(100*sizeof(char));//String for append
	char* sStr = (char*)malloc(100*sizeof(char));//String for subset

	//Exit terminates the program
	while( c != 'q'){
		c = getchar();

		//Handles create
		if(c == 'c'){
			free(head);
			fgets(cStr,100,stdin);
			fgets(cStr,100,stdin);

			if(cStr[strlen(cStr) -1] == 10){
				cStr[strlen(cStr) -1] = 0;
			}
			head = createExp(cStr);
			//free(expression);
		}

		//Handles print
		else if(c == 'p'){
			printExpression(head);
			
		}

		//Handles Append
		else if(c == 'a'){
			fgets(aStr,100,stdin);
			fgets(aStr,100,stdin);

			if(aStr[strlen(aStr) -1] == 10){
				aStr[strlen(aStr) -1] = 0;
			}
			appendExpression(head,aStr);
			//free(appendStr);
			//char x;
		}

		//Handles subset
		else if(c == 's'){
			fgets(sStr,100,stdin);
			fgets(sStr,100,stdin);
			printSubset(head,sStr);
			//free(subset);
		}
		else if(c == 'e'){
			evaluate(head);
		}
	}
	//free(x);
	return 0;	
	//*/
}

