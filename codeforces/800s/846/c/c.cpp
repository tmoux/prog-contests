#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n;
ll pre[maxn];

struct Sparse
{
    //sparse table data structure for min
    static const int mk = 15; //change this number based on bounds
    ll* tb[mk];
    static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
    Sparse(ll *a, int n) {
        for (int i = 0; i < mk; i++) {
            tb[i] = new ll[n+1];
        }
        for (int i = 0; i <= n; i++) tb[0][i] = a[i];
        for (int k = 1; k < mk; k++) {
            for (int i = 0; i <= n; i++) {
                int nx = i + (1<<(k-1));
                if (nx <= n) tb[k][i] = min(tb[k-1][i],tb[k-1][nx]);
                else tb[k][i] = tb[k-1][i];
                //cout << i << ' ' << k << ": " << tb[k][i] << '\n';
            }
        }
    }
    ll getmin(int l, int r) {
        int g = lg(r-l+1);
        return min(tb[g][l],tb[g][r-(1<<g)+1]);
    }
};

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pre[i];
        pre[i] += pre[i-1];
    }
    ll bestans = -1e18;
    vector<int> ret;
    for (int l = 0; l <= n; l++) {
        int idx = l;
        for (int r = l; r <= n; r++) {
            if (pre[r] < pre[idx]) {
                idx = r;
            }

            ll tr = pre[l] - pre[idx] + pre[r];
            //printf("%d %d %d: %lld\n",l,idx,r,tr);
            if (bestans < tr) {
                bestans = tr;
                ret = {l,idx,r};
            }
        }
    }
    for (int i: ret) {
        cout << i << ' ';
    }
    cout << '\n';
}

