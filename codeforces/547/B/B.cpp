#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, maxk = 19;
int n, logk, A[maxn], rmin[maxk][maxn];
inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
int query(int l, int r) {
    int k = lg(r-l+1);
    return min(rmin[k][l],rmin[k][r-(1<<k)+1]);
}
int ans[maxn];

int getLeft(int i) { //returns leftmost such that query(l,i) == A[i]
    int res = i;
    for (int k = lg(i+1); k >= 0; --k) {
        int nl = res - (1 << k);
        if (nl < 0) continue;
        if (query(nl,i) == A[i]) {
            res = nl;
        }
    }
    return res;
}

int getRight(int i) {
    int res = i;
    for (int k = lg(n-i+1); k >= 0; --k) {
        int nr = res + (1 << k);
        if (nr >= n) continue;
        if (query(i,nr) == A[i]) {
            res = nr;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n; logk = lg(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) rmin[0][i] = A[i];
    for (int k = 1; k <= logk; k++) {
        for (int i = 0; i < n; i++) {
            int nx = i + (1 << (k-1));    
            if (nx >= n) nx = n - (1 << (k-1));
            rmin[k][i] = min(rmin[k-1][i],rmin[k-1][nx]);
        }
    }

    for (int i = 0; i < n; i++) {
        int l = getLeft(i), r = getRight(i);
        int dist = r-l+1;
        ans[dist] = max(ans[dist],A[i]);
    }

    //output
    for (int i = n-1; i >= 1; i--) {
        ans[i] = max(ans[i],ans[i+1]);    
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}
	

