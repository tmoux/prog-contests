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
	int longest = 1;
	char currchar = s[0];
	int currlen = 1;
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == currchar) currlen++;
		else {
			currlen = 1;
			currchar = s[i];
		}
		longest = max(longest,currlen);
	}
	cout << longest << '\n';
	return 0;
}

