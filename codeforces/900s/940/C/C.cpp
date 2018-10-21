#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int n, k;
string s;
char chars[52];
set<char> setchars;
map<char,int> charToInt;
int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> k >> s;
	string t = "";
	for (int i = 0; i < k; i++) {
		t += ' ';
	}
	for (int i = 0; i < n; i++) {
		setchars.insert(s[i]);
	}
	int counter = 0;
	for (auto it: setchars) {
		charToInt[it] = counter;
		chars[counter] = it;
		counter++;
	}

	char lastchar = chars[n-1];
	for (int i = 0; i < n; i++) {
		chars[i+n] = chars[i];
	}
	if (n < k) {
		for (int i = 0; i < k; i++) {
			if (i != k - 1) {
				t[i] = s[i];
			}
			else {
				t[i] = chars[0];
			}
		}
	}
	else {
		bool rollOver = true;
		for (int i = k-1; i >= 0; i--) {
			if (rollOver) {
				t[i] = chars[(charToInt[s[i]]+1) % n];
			}
			else {
				t[i] = s[i];
			}
			if (s[i] != lastchar) {
				rollOver = false;
			}
			cout << t[i] << '\n';
		}
	}
	cout << t << '\n';
	
	return 0;
}

