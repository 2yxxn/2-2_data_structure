// 2019204034 ������
#include <iostream>
#include <stack>
#include <fstream>
#include <string> // getline()
#include <vector>
#include <cstring>

using namespace std;

void separate_file(char firstarr[][3], char secondarr[][3], char thirdarr[][3]);
// operations.txt ������ �о @, #, & ������ �迭�� �����ϴ� �Լ�
void replace_postfix(vector<char>& postfix, stack<char>& op, string expression, int& errorsign);
// �Էµ� ���� postfix�� ���·� �ٲٴ� �Լ�
void calculation(int& errorsign, vector<char>& postfix, stack<char>& op, char firstarr[][3], char secondarr[][3], char thirdarr[][3]);
// postfix�� ����ϴ� �Լ�

int main() {
	char firstarr[3][3];
	char secondarr[3][3];
	char thirdarr[3][3];

	separate_file(firstarr, secondarr, thirdarr);

	while (1) {
		vector<char> postfix;	// postfix�� �ٲ� ���� ������ vector
		stack<char> op;			// postfix�� ���� ��ȯ�ϱ� ���� ��ȣ�� �����ڸ� ������ stack
		string expression;		// �Էµ� ���� ������ string
		int errorsign = 0;		// ��Ȱ�� ����� ���� error�� üũ�ϴ� ����

		cin >> expression;
		if (expression == "EOI") { // EOI�� �ԷµǸ� ���α׷� ����
			return 0;
		}
		replace_postfix(postfix, op, expression, errorsign);
		calculation(errorsign, postfix, op, firstarr, secondarr, thirdarr);
	}
	return 0;
}

void separate_file(char firstarr[][3], char secondarr[][3], char thirdarr[][3]) {
	string file = "operations.txt";
	ifstream readfile;

	readfile.open(file);
	if (readfile.is_open()) {
		while (!readfile.eof()) {
			string str;
			char c;
			getline(readfile, str);

			if (str == "@") {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						readfile.get(c);
						if (c == ' ' || c == '\n')
							readfile.get(c);
						firstarr[i][j] = c;
					}
				}
			}

			readfile.get(c);
			getline(readfile, str);
			if (str == "#") {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						readfile.get(c);
						if (c == ' ' || c == '\n')
							readfile.get(c);
						secondarr[i][j] = c;
					}
				}
			}

			readfile.get(c);
			getline(readfile, str);
			if (str == "&") {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						readfile.get(c);
						if (c == ' ' || c == '\n')
							readfile.get(c);
						thirdarr[i][j] = c;
					}
				}
			}
		}
		readfile.close();
	}
}

void replace_postfix(vector<char>& postfix, stack<char>& op, string expression, int& errorsign) {
	for (size_t i = 0; i < expression.size(); i++) {
		if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
			op.push(expression[i]);
		}
		else if (expression[i] == 'a' || expression[i] == 'b' || expression[i] == 'c') {
			postfix.push_back(expression[i]);
		}
		else if (expression[i] == '&' || expression[i] == '#' || expression[i] == '@') {
			if (op.empty() == 1) {
				op.push(expression[i]);
			}
			else if (op.top() == '(' || op.top() == '{' || op.top() == '[') {
				op.push(expression[i]);
			}
			else {
				if (expression[i] == '&') {
					op.push(expression[i]);
				}
				else {
					postfix.push_back(op.top());
					op.pop();
					op.push(expression[i]);
				}
			}
		}
		else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
			if (expression[i] == ')') {
				if (op.empty() == 1) {
					cout << "Error!" << endl;
					errorsign = 1;
					break;
				}
				while (op.top() != '(') {
					if (op.top() == '{' || op.top() == '[') {
						cout << "Error!" << endl;
						errorsign = 1;
						break;
					}
					postfix.push_back(op.top());
					op.pop();
				}
				if (errorsign == 1)
					break;
				op.pop();
			}
			else if (expression[i] == '}') {
				if (op.empty() == 1) {
					cout << "Error!" << endl;
					errorsign = 1;
					break;
				}
				while (op.top() != '{') {
					if (op.top() == '(' || op.top() == '[') {
						cout << "Error!" << endl;
						errorsign = 1;
						break;
					}
					postfix.push_back(op.top());
					op.pop();
				}
				if (errorsign == 1)
					break;
				op.pop();
			}
			else if (expression[i] == ']') {
				if (op.empty() == 1) {
					cout << "Error!" << endl;
					errorsign = 1;
					break;
				}
				while (op.top() != '[') {
					if (op.top() == '{' || op.top() == '(') {
						cout << "Error!" << endl;
						errorsign = 1;
						break;
					}
					postfix.push_back(op.top());
					op.pop();
				}
				if (errorsign == 1)
					break;
				op.pop();
			}
		}
		else {		// a, b, c, (), {}, []�� ������ �Է��� ������ ���
			cout << "Wrong input" << endl;
			errorsign = 1;
			break;
		}
	}
}

void calculation(int& errorsign, vector<char>& postfix, stack<char>& op, char firstarr[][3], char secondarr[][3], char thirdarr[][3]) {
	if (errorsign == 0) {
		while (!op.empty()) {
			postfix.push_back(op.top());
			op.pop();
		}
		stack<char> cal;
		char answer;
		char op1, op2;
		int j, k;
		for (size_t i = 0; i < postfix.size(); i++) {
			if (postfix[i] == 'a' || postfix[i] == 'b' || postfix[i] == 'c') {
				cal.push(postfix[i]);
			}
			else {
				op2 = cal.top();
				switch (cal.top()) {
				case 'a':
					j = 0;
					break;
				case 'b':
					j = 1;
					break;
				case 'c':
					j = 2;
					break;
				default:
					break;
				}
				cal.pop();
				op1 = cal.top();
				switch (cal.top()) {
				case 'a':
					k = 0;
					break;
				case 'b':
					k = 1;
					break;
				case 'c':
					k = 2;
					break;
				default:
					break;
				}
				cal.pop();
				switch (postfix[i]) {
				case '&':
					cal.push(thirdarr[k][j]);
					break;
				case '#':
					cal.push(secondarr[k][j]);
					break;
				case '@':
					cal.push(firstarr[k][j]);
					break;
				default:
					break;
				}
			}
		}
		answer = cal.top();
		cout << answer << endl;
	}
}