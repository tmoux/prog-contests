#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define all(x) begin(x),end(x)

const int maxn = 2e5+5;
int N, Q, A[maxn];
vector<ll> node[4*maxn];
vector<ll> pfx[4*maxn];
int s[4*maxn], e[4*maxn];

void build(int i, int l, int r) {
    s[i] = l;
    e[i] = r;
    if (l == r) {
        node[i] = {A[l]};
        pfx[i] = {A[l]};
        return;
    }
    int m = (l+r)>>1;
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    node[i].resize(node[i*2].size()+node[i*2+1].size());
    merge(all(node[i*2]),all(node[i*2+1]),node[i].begin());
    pfx[i].resize(node[i].size());
    for (int j = 0; j < pfx[i].size(); j++) {
        pfx[i][j] = node[i][j];
        if (j > 0) pfx[i][j] += pfx[i][j-1];
    }
    /*
    printf("%d %d:\n",l,r);
    for (int a: node[i]) cout << a << ' ';
    cout << '\n';
    for (int a: pfx[i]) cout << a << ' ';
    cout << "\n\n";
    */
}

ll query(int i, int l, int r, int k) {
    if (l > e[i] || r < s[i]) return 0;
    if (l <= s[i] && e[i] <= r) {
        auto it = lower_bound(all(node[i]),k);
        if (it == node[i].end()) {
            return -pfx[i].back();
        }
        int j = it-node[i].begin();
        if (j == 0) {
            return pfx[i].back();
        }
        else {
            ll geq = pfx[i].back() - pfx[i][j-1];
            ll smol = pfx[i][j-1];
            return geq - smol;
        }
    }
    return query(i*2,l,r,k) + query(i*2+1,l,r,k);
}
    
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> A[i];
    build(1,1,N); 
    while (Q--) {
        int l, r, k; cin >> l >> r >> k;
        cout << query(1,l,r,k) << '\n';
    }

    return 0;
}

