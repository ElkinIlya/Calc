#include "Calc.h"

Calc::Calc(const char* _expr) : result(0.0f) {
	int p = 0;
	expr_len = 0;
	expr_RPN_len = 0;
	for(int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j) {
			expr[i][j] = '#';
			expr_RPN[i][j] = '#';
		}
	while (p < std::strlen(_expr) - 1) {
		if (_expr[p] != ' ') {
			bool fl = false;
			for (int i = 0; i < 7; ++i) {
				if (operc[i] == _expr[p] && (_expr[p] != '-' || p != 0 && _expr[p - 1] != '('))
					fl = true;
			}
			if (fl) {
				expr[expr_len][0] = _expr[p];
				expr_len++;
				++p;
			}
			else {
				int sgn = 1;
				int first = p;
				if (_expr[p] == '-') sgn = -1, ++p;
				while (isalnum(_expr[p]) || _expr[p] == '.' || _expr[p] == ',' || _expr[p] == 'e' || (p > 0 && (_expr[p] == '+' || _expr[p] == '-') && _expr[p-1] == 'e')) ++p;
				int str_len = p - first + 1;
				char* tmp_str = new char[str_len];
				for (int i = 0; i < str_len - 1; ++i) {
					expr[expr_len][i] = _expr[first + i];
				}
				expr_len++;
			}
			/*if (operc.count(_expr[p]) && (_expr[p] != '-' || p != 0 && _expr[p - 1] != '(')) {
				expr.push_back(std::string(1, _expr[p]));
				++p;
			}
			else {
				int sgn = 1;
				int first = p;
				if (_expr[p] == '-') sgn = -1, ++p;
				while (isalnum(_expr[p]) || _expr[p] == '.' || _expr[p] == ',') ++p;
				expr.push_back(std::string(_expr.begin() + first, _expr.begin() + p));
			}*/
		}
		else ++p;
	}

	exprToRPN();

	RPNToResult();
}

//vector<string> -> vector<string>, each string - "int" or "char"
void Calc::exprToRPN() {
	
	Stack<char*> X;
	Stack<char*> Y;
	
	for (int i = 0; i < int(expr_len - 1); ++i) {
		bool fl = false;
		for (int j = 0; j < 7; ++j) {
			if (operc[j] == expr[i][0])
				fl = true;
		}
		if (fl) {
			if (expr[i][0] == ')') {
				while (Y.top()[0] != '(') {
					X.push(Y.top());
					Y.pop();
				}
				Y.pop();
			}
			else {
				int in1, in2;
				in1 = in2 = 0;
				if (Y.size() != 0) {
					while (in1 < 6 && priority[in1].c[0] != expr[i][0]) in1++;
					if (in1 == 6) in1 = 0;
					while (in2 < 6 && priority[in2].c[0] != Y.top()[0]) in2++;
					if (in2 == 6) in2 = 0;
					in1 = priority[in1].p;
					in2 = priority[in2].p;
				}
				if (Y.size() == 0 || expr[i][0] == '(' || in1 > in2) {
					Y.push(expr[i]);
				}
				else {
					X.push(Y.top());
					Y.pop();
					Y.push(expr[i]);
				}
			}
		}
		else {
			X.push(expr[i]);
		}
	}

	while (Y.size()) {
		X.push(Y.top());
		Y.pop();
	}
	
	while (X.size() != 0) {
		//expr_RPN.push_back(X.top());.
		for (int i = 0; i < 100; ++i)
			expr_RPN[expr_RPN_len][i] = X.top()[i];
		//strcpy_s(expr_RPN[expr_RPN_len], X.top());
		//expr_RPN[expr_RPN_len] = X.top();
		expr_RPN_len++;
		X.pop();
	}
	for (int i = 0; i < expr_RPN_len / 2; ++i)
		std::swap(expr_RPN[i], expr_RPN[expr_RPN_len - i - 1]);
	expr_RPN[expr_RPN_len][0] = '=';
	//expr_RPN.push_back("=");
	std::cout << "RPN: ";
	for (int i = 0; i < expr_RPN_len; ++i)
		for (int j = 0; expr_RPN[i][j] != '#'; ++j)
			std::cout << expr_RPN[i][j] << " ";
	std::cout << std::endl;
}

void Calc::RPNToResult() {
	Stack<float> q;
	
	for (int i = 0; i < expr_RPN_len; ++i) {
		bool fl = false;
		for (int j = 0; j < 7; ++j) {
			if (operc[j] == expr_RPN[i][0])
				fl = true;
		}
		if ('0' <= (expr_RPN[i][1]) && (expr_RPN[i][1]) <= '9') fl = false;
		if (fl) {
			float t1, t2;
			
			t1 = q.top();
			q.pop();
			
			t2 = q.top();
			q.pop();
			
			if (expr_RPN[i][0] == '+') {
				q.push(t1 + t2);
			}
			else if (expr_RPN[i][0] == '-') {
				q.push(t2 - t1);
			}
			else if (expr_RPN[i][0] == '*') {
				q.push(t1 * t2);
			}
			else if (expr_RPN[i][0] == '/') {
				if (t1 == 0) {
					std::cerr << "Division by 0" << std::endl;
					system("pause");
					exit(-2);
				}
				q.push(t2 / t1);
			}
			else {
				std::cerr << "Something weird happened!" << std::endl;
				system("pause");
				exit(-1);
			}
		}
		else {
			q.push(std::atof(expr_RPN[i]));
		}
	}

	result = q.top();
}

void Calc::printResult() {
	std::cout << result << std::endl;
}