// 2019204034 ÀÌÀ±Áö
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() { 
	unordered_map<string, int> count_password;
	int cut;
	string pass;

	cin >> cut;
	cin >> pass;

	for (size_t i = 0; i <= pass.size() - cut; i++) {
		if (count_password.count(pass.substr(i, cut)))
			count_password[pass.substr(i, cut)]++;
		else
			count_password.insert({ pass.substr(i, cut), 1 });
	}

	unordered_map<string, int>::iterator iter;
	iter = count_password.begin();
	int max = iter->second;
	string found = iter->first;
	++iter;
	for (; iter != count_password.end(); ++iter) {
		if (max < iter->second) {
			max = iter->second;
			found = iter->first;
		}
	}

	cout << found <<endl;
	
	return 0; 
}