#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m;
int a[maxn][30];
struct Seg
{
	int *s, *e, *sum;
	Seg(int l, int r) {
		int n = r-l+1;
		s = new int[4*n];
		e = new int[4*n];
		sum = new int[4*n];
		build(1,l,r);
	}
	void build(int i, int l, int r) {
		s[i] = l;
		e[i] = r;
		if (l == r) {
            sum[i] = 0;
            for (int k = 0; k < 30; k++) {
                sum[i] += a[l][k] * (1<<k);    
            }
            //cout << l << ' ' << r << ": " << sum[i] << '\n';
			return;
		}
		int m = (l+r)/2;
		build(i*2,l,m);
		build(i*2+1,m+1,r);
		sum[i] = sum[i*2] & sum[i*2+1];
        //cout << sum[i*2] << " " << sum[i*2+1] << '\n';
        //cout << l << ' ' << r << ": " << sum[i] << '\n';
	}
	
	int getsum(int i, int l, int r) {
		if (l <= s[i] && e[i] <= r) return sum[i];
        int res = (1<<30)-1;
        int m = (s[i]+e[i])/2;
        if (l <= m) {
            res &= getsum(i*2,l,r);
        }
        if (r > m) {
            res &= getsum(i*2+1,l,r);
        }
        return res;
	}
};

struct Query
{
    int li, ri, qi;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<Query> queries;
    while (m--) {
        int l, r, q; cin >> l >> r >> q;
        queries.push_back({l,r,q});
        for (int k = 0; k < 30; k++) {
            if (q & (1<<k)) {
                a[l][k]++;
                a[r+1][k]--;
            }
        }
    }
    for (int k = 0; k < 30; k++) {
        for (int i = 1; i <= n; i++) {
            a[i][k] += a[i-1][k];        
        }
    }
    for (int k = 0; k < 30; k++) {
        for (int i = 1; i <= n; i++) {
            a[i][k] = min(a[i][k],1);
        }
    }
   
    Seg seg(1,n);
    for (Query qu: queries) {
        if (!(seg.getsum(1,qu.li,qu.ri) == qu.qi)) {
            cout << "NO\n";
            return 0;
        }
    }
    //possible
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << seg.getsum(1,i,i) << ' ';
    }
    cout << '\n';

    return 0;
}

