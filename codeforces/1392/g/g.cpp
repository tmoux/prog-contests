#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, maxk = 20;
int n, m, k;
vector<int> perm[maxn];
vector<bool> orig, target;
vector<bool> pfx_orig[maxn], pfx_target[maxn];

int Left[1<<maxk], Right[1<<maxk];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    string s;
    cin >> s;
    orig.resize(k);
    target.resize(k);
    for (int i = 0; i < k; i++) {
        orig[i] = s[i] == '1';
    }
    cin >> s;
    for (int i = 0; i < k; i++) {
        target[i] = s[i] == '1';
    }
    perm[0].resize(k);
    iota(perm[0].begin(),perm[0].end(),0);
    auto compose = [&](vector<int>& a, vector<int>& b) {
        assert(a.size() == k && b.size() == k);
        vector<int> ret(k);
        for (int i = 0; i < k; i++) {
            ret[i] = b[a[i]];
        }
        return ret;
    };
    auto apply = [&](vector<int>& p, vector<bool> a) {
        vector<bool> ret(k);
        for (int i = 0; i < k; i++) {
            ret[i] = a[p[i]];
        }
        return ret;
    };
    for (int i = 1; i <= n; i++) {
        vector<int> p(k);
        iota(p.begin(),p.end(),0);
        int a, b; cin >> a >> b;
        --a; --b;
        swap(p[a],p[b]);
        perm[i] = compose(perm[i-1],p);
    }
    for (int i = 0; i <= n; i++) {
        pfx_orig[i] = apply(perm[i],orig);        
        pfx_target[i] = apply(perm[i],target);        
    }
    /*
    for (int i = 0; i <= n; i++) {
        cout << i << ": ";
        for (auto j: pfx_orig[i]) {
            cout << j << ' ';
        }
        cout << '\n';
    }
    cout << "target:\n";
    for (int i = 0; i <= n; i++) {
        cout << i << ": ";
        for (auto j: pfx_target[i]) {
            cout << j << ' ';
        }
        cout << '\n';
    }
    */
    auto get_mask = [&](vector<bool>& a) {
        int res = 0;
        for (int i = 0; i < k; i++) {
            if (a[i]) res += 1<<i;
        }
        return res;
    };
    memset(Left,-1,sizeof Left);
    memset(Right,-1,sizeof Right);
    for (int i = 0; i < n; i++) {
        int mask = get_mask(pfx_orig[i]);        
        if (Left[mask] == -1) Left[mask] = i;
        else Left[mask] = min(Left[mask],i);
    }
    for (int i = n; i >= 1; i--) {
        int mask = get_mask(pfx_target[i]);
        Right[mask] = max(Right[mask],i);
    }
    for (int i = (1<<k)-1; i >= 1; i--) {
        for (int j = 0; j < k; j++) {
            if (i&(1<<j)) {
                int nm = i^(1<<j);
                if (Left[i] != -1) {
                    if (Left[nm] == -1) Left[nm] = Left[i];
                    else Left[nm] = min(Left[nm],Left[i]);
                }
                if (Right[i] != -1) {
                    Right[nm] = max(Right[nm],Right[i]);
                }
            }
        }
    }
    int ans = k;
    for (int i = 0; i < k; i++) {
        if (orig[i]) ans--;
        if (target[i]) ans--;
    }
    int common = 0;
    pair<int,int> ret = {1,n};
    for (int i = 1; i < (1<<k); i++) {
        if (Left[i] != -1 && Right[i] != -1 && Right[i]-Left[i] >= m) {
            if (__builtin_popcount(i) > common) {
                common = __builtin_popcount(i);
                ret = make_pair(Left[i]+1,Right[i]);
            }
        }
    }
    ans += 2*common;
    //cout << "common = " << common << endl;
    cout << ans << '\n';
    cout << ret.first << ' ' << ret.second << '\n';
}
