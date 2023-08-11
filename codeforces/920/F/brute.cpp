#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5, maxx = 1e6+6;
int n, m, A[maxn], prime[maxx];

void sieve() {
    for (int i = 2; i*i < maxx; i++) {
        if (!prime[i]) {
            for (int j = i*i; j < maxx; j += i) {
                prime[j] = i;
            }
        }
    }
    for (int i = 2; i < maxx; i++) {
    	if (!prime[i]) prime[i] = i;
    }
}

int div(int x) {
	int res = 1;
	while (x > 1) {
		int p = prime[x];
		int cnt = 1;
		while (x % p == 0) {
			x /= p;
			cnt++;
		}
		res *= cnt;
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    sieve();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> A[i];
    while (m--) {
        int t; cin >> t;
        int l, r; cin >> l >> r;
        if (t == 1) {
            for (int i = l; i <= r; i++) {
                A[i] = div(A[i]);
            }
        }
        else {
            ll sum = 0;
            for (int i = l; i <= r; i++) {
                sum += A[i];
            }
            cout << sum << '\n';
        }
    }

    return 0;
}

