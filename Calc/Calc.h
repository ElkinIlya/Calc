#pragma once
//#include <string>
#include "Stack.h"
//#include <set>
//#include <unordered_map>
//#include <vector>
#include <iostream>

struct prOps {
	const char* c;
	int p;
	prOps(const char* ch, int pr) :c(ch), p(pr) {}
};

class Calc {
public:
	Calc(const char* _expr);

	void printResult();

private:
	int expr_len;
	int expr_RPN_len;
	//std::vector<std::string> expr;
	char expr[100][100];

	//std::vector<std::string> expr_RPN;
	char expr_RPN[100][100];

	//std::set<std::string> opers = {"=", "+", "-", "*", "/", "(", ")" };
	const char* opers[7] = { "=", "+", "-", "*", "/", "(", ")" };
	
	//std::set<char> operc = {'=', '+', '-', '*', '/', '(', ')'};
	char operc[7] = { '=', '+', '-', '*', '/', '(', ')' };

	//std::unordered_map<std::string, int> priority = { {"=", 1}, {"(", 2}, {"-", 3}, {"+", 3}, {"*", 4}, {"/", 4} };
	prOps priority[6] = { {"=", 1}, {"(", 2}, {"-",3 }, {"+", 3}, {"*",4}, {"/", 4} };

	void exprToRPN();

	void RPNToResult();

	float result;
};