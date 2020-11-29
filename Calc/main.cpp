#include "Calc.h"
#include "Stack.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	char s[100];
	
	Stack<int> st;
	
	fgets(s, sizeof(s), stdin);
	
	Calc calculator(s);

	calculator.printResult();

	system("pause");
}