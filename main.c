#include "expression.h"


int main(){

	Exp* head;

	head = createExp("(+ (+ (+ 1 2) 3) 4)");
	//head = createExp("2");
	//head = createExp("(+ 55 65 3 5 6 (* 5 6 7 (- 565 767565 (- 5 5)) 8 88) (+ 45545 54 4545 545))");
	printExpression(head);

	//printf("%s\n",head->first->symbol );





	return 0;
}