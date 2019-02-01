#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
const int MAX = 5;
int N, K, mn[maxn], a[maxn];

bool check(const vector<int>& v) {
	for (int i = 1; i <= N-K+1; i++) {
		int m = MAX + 1;
		for (int j = i; j < i+K; j++) {
			m = min(m,v[j-1]);
		}
		//cout << i << ": " << mn[i] << "," << m << '\n';
		if (m != mn[i]) return false;
	}
	return true;
}

int ans = 0;
void recurse(int i, vector<int> v) {
	if (i == N + 1) {
		if (check(v)) {
			for (int j: v) {
				cout << j << ' ';
			}
			cout << '\n';
			ans = (ans + 1) % M;
		}
		return;
	}
	for (int j = 1; j <= MAX; j++) {
		v.push_back(j);
		recurse(i+1,v);
		v.pop_back();
	}
}

int main()
{
	cin >> N >> K;
	for (int i = 1; i <= N-K+1; i++) {
		cin >> mn[i];
	}
	recurse(1,vector<int>());
	cout << "ans: " << ans << '\n';
	
	return 0;
}
