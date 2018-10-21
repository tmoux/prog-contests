#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

list<list<int>*> zebras, offzebras;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	string s; cin >> s;
	bool ans = true;
	for (int i = 0; i < s.size(); i++) {
		bool isOne = s[i] == '1';
		if (!isOne) {
			if (offzebras.empty()) {
				list<int>* newlist = new list<int>(1,i);
				zebras.push_back(newlist);
			}
			else {
				list<int>* last = offzebras.back();
				offzebras.pop_back();
				last->push_back(i);
				zebras.push_back(last);
			}			
		}
		else {
			if (!zebras.empty()) {
				list<int>* last = zebras.back();
				zebras.pop_back();
				last->push_back(i);
				offzebras.push_back(last);
			}
			else {
				ans = false;
				break;
			}
		}
	}
	
	if (!ans || !offzebras.empty()) {
		cout << "-1\n";
	}
	else {
		cout << zebras.size() << '\n';
		for (list<int>* ptr: zebras) {
			cout << ptr->size() << ' ';
			for (int i: *ptr) {
				cout << i+1 << ' ';
			}
			cout << '\n';
		}
	}
	return 0;
}

