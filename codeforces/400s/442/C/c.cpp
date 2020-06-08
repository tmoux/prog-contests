#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
#define mp make_pair

const int maxn = 5e5+5;
int n, a[maxn];
int Left[maxn], Right[maxn];
bool used[maxn];

int calc(int i) {
	return min(a[Left[i]],a[Right[i]]);
}

bool check(int i) {
	if (used[i]) return false;
	if (i == 0 || i == n+1) return false;
	return a[Left[i]] >= a[i] && a[i] <= a[Right[i]];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    Right[0] = 1;
    for (int i = 1; i <= n; i++) {
    	cin >> a[i];
    	Left[i] = i-1;
    	Right[i] = i+1;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
    	if (check(i)) {
    		used[i] = true;
    		q.push(i);
    	}
    }
    ll ans = 0;
    //cout << Right[0] << endl;
    while (!q.empty()) {
    	int i = q.front(); q.pop();
    	//cout << i << endl;
    	ans += calc(i);
    	Right[Left[i]] = Right[i];
    	Left[Right[i]] = Left[i];
    	if (check(Left[i])) {
    		used[Left[i]] = true;
    		q.push(Left[i]);
    	}
    	if (check(Right[i])) {
    		used[Right[i]] = true;
    		q.push(Right[i]);
    	}
    }
    //cout << Right[0] << endl;
    int i = Right[0];
    while (i != n+1) {
    	//cout << a[Left[i]] << ' ' << a[i] << ' ' << a[Right[i]] << ": " << calc(i) << endl;
    	ans += calc(i);
    	i = Right[i];
    }
    cout << ans << '\n';
}

