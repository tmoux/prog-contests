#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int num[3];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	string s; cin >> s;
	bool seenB = false, seenC = false, poss = true;
	for (int i = 0; i < s.size(); i++) {
		num[s[i]-'a']++;
		if (s[i] == 'b') {
			seenB = true;
		}
		if (s[i] == 'c') {
			seenC = true;
		}
		if (seenB && s[i] == 'a' || (seenC && (s[i] == 'a' || s[i] == 'b'))) {
			poss = false;
		}
	}
	if (poss && (num[2] == num[0] || num[2] == num[1]) && num[0] > 0 && num[1] > 0) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	
	
	return 0;
}