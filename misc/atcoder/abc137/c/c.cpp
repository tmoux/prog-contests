#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<char> form(string s) {
	vector<char> res;
	for (char c: s) {
		res.push_back(c);
	}
	sort(res.begin(),res.end());
	return res;
}

int main()
{
	int N; cin >> N;
	map<vector<char>,int> mp;
	ll ans = 0;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		auto p = form(s);
		ans += mp[p];
		mp[p]++;
	}
	cout << ans << '\n';
}