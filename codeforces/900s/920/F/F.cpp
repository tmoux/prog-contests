#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5, maxx = 1e6+6;
int n, m, prime[maxx], A[maxn];

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

ll sum[4*maxn];
int mx[4*maxn];
int s[4*maxn], e[4*maxn];

void build(int i, int l, int r) {
    s[i] = l;
    e[i] = r;
    if (l == r) {
        sum[i] = A[l];
        mx[i] = A[l];
        return;
    }
    int m = (l+r)>>1;
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    sum[i] = sum[i*2] + sum[i*2+1];
    mx[i] = max(mx[i*2],mx[i*2+1]);
}

ll query(int i, int l, int r) {
    if (l > e[i] || r < s[i]) return 0;
    if (l <= s[i] && e[i] <= r) return sum[i];
    return query(i*2,l,r) + query(i*2+1,l,r);
}

void update(int i, int l, int r) {  
    if (l > e[i] || r < s[i]) return;
    if (l <= s[i] && e[i] <= r && mx[i] <= 2) return;
    if (s[i] == e[i]) {
        sum[i] = div(sum[i]);
        mx[i] = sum[i];
        return;
    }
    update(i*2,l,r);
    update(i*2+1,l,r);
    sum[i] = sum[i*2] + sum[i*2+1];
    mx[i] = max(mx[i*2],mx[i*2+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    sieve();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
    	int ai; cin >> A[i];
    }
    build(1,1,n);

    while (m--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 1) {
            update(1,l,r);
        }
        else {
            ll ans = query(1,l,r);
            cout << ans << '\n';
        }
    }

    return 0;
}
