#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n;
string strings[100005];

long long countHS(const string& s) {
	int numhs = 0;
	for (char c: s) {
		if (c == 'h') numhs++;
	}
	long long total = 0;
	for (char c: s) {
		if (c == 's') total += numhs;
		else numhs--;
	}
	return total;
}


int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	string master = "";
	
	for (int i = 0; i < n; i++) {
		cin >> strings[i];
	}
	
	sort(strings,strings+n, [&](string a, string b) {
		return countHS(a+b) > countHS(b+a);
	});
	
	for (int i = 0; i < n; i++) {
		master += strings[i];
	}
	//cout << master << '\n';
	cout << countHS(master) << '\n';
	
	return 0;
}

