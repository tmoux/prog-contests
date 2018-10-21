#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+20;
ll bit[maxn];
int n;
ll t;

int sum(int x) {
	ll res = 0;
	while (x) {
		res += bit[x];
		x -= x & (-x);
	}
	return res;
}

void add(int x, int val) {
	while (x <= n+2) {
		bit[x] += val;
		x += x & (-x);
	}
}

int main()
{	
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> t;


    return 0;
}







