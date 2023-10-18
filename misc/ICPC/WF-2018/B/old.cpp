#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef long double ld; // change to double if appropriate
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define F0Rd(i, a) for (int i = (a) - 1; i >= 0; i--)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const char nl = '\n';

void solve() {
	string line;
	getline(cin, line);
	stringstream ss(line);
	vector<string> v, words;
	string s;
	map<string, int> mp;
	vector<int> Idx;
	int cc = 0;
	while (ss >> s) {
		v.push_back(s);
		string t = s;
		if (t.back() == ',' || t.back() == '.') t.pop_back();
		words.push_back(t);
		if (!mp.count(t)) mp[t] = cc++;
		Idx.push_back(mp[t]);
	}

	vector<vector<vector<int>>> adj(cc, vector<vector<int>>(2));
	// 0 = fwd, 1 = back
	queue<pair<int, int>> q;
	vector<vector<>> adj(cc, vector<vector<int>>(2));
	ve
	set<pair<string, int>> S;
	F0R(i, sz(v)) {
		if (i + 1 < sz(v)) {
			if (v[i].back() != '.') {
				adj[{words[i], 0}].push_back(words[i+1]);
				adj[{words[i+1], 1}].push_back(words[i]);
			}
			if (v[i].back() == ',') {
				q.push({words[i], 0});
				S.insert({words[i], 0});
			}
		}
	}
	while (!q.empty()) {
		auto [t, i] = q.front(); q.pop();
		for (auto s: adj[{t, i}]) {
			if (!S.count({s, i^1})) {
				S.insert({s, i^1});
				q.push({s, i^1});
			}
		}
	}

	F0R(i, sz(v)-1) {
		if (v[i].back() == '.') cout << v[i] << ' ';
		else if (S.count({words[i], 0})) {
			cout << words[i] << ", ";
		}
		else cout << words[i] << ' ';
	}
	cout << v.back() << '\n';

}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	solve();
	return 0;
}
