#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	string s; cin >> s;
	int curr = 'a';
	if (s.size() < 26) {
		cout << "-1\n";
		return 0;
	}
	for (int i = 0; i < s.size(); i++) {
		if (s[i] <= curr) {
			s[i] = curr;
			curr++;
			if (curr > 'z') break;
		}
	}
	if (curr > 'z') {
		cout << s << '\n';
	}
	else {
		cout << "-1\n";
	}
	
	
	return 0;
}

