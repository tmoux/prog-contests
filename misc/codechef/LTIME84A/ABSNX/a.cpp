#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 250005;
int N;
int a[maxn];

int binsearch(vector<pair<int,int>>& v, int ai) {
    int lo = 0, hi = v.size();
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (v[mid].second >= ai) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    return lo;
}

bool first = true;
ll f(int l, int r) {
    if (l == r) {
        return first?1LL:0LL;
    }
    int m = (l+r)/2;
    ll res = f(l,m) + f(m+1,r);
    int mx = 0;
    vector<pair<int,int>> v;
    int mnR = 2e9;
    ll loc = 0;
    for (int i = m+1; i <= r; i++) {
        mx = max(mx,a[i]);
        mnR = min(mnR,a[i]);
        if (a[i] == mx) {
            v.push_back({a[i],mnR});
        }
    }
    int mn = 2e9;
    int mxL = 0;
    for (int i = m; i >= l; i--) {
        mn = min(mn,a[i]);
        mxL = max(mxL,a[i]);
        if (a[i] == mn) {
            auto it = lower_bound(begin(v),end(v),first?make_pair(mxL,0):make_pair(max(a[i]+1,mxL),0));
            int idx = distance(begin(v),it);
            int r = binsearch(v,a[i]);
            res += max(0,r-idx+1);
            loc += max(0,r-idx+1);
            /*
            for (auto j = it; j != end(v); ++j) {
                cout << i << ' ' << (*j) << '\n';
            }
            */
        }
    }
    //cout << l << ' ' << m << ' ' << r << ": " << loc << '\n';
    return res;
}

ll brute() {
    ll res = 0;
    for (int l = 0; l < N; l++) {
        for (int r = l; r < N; r++) {
            int mn = 2e9, mx = -2e9;
            for (int i = l; i <= r; i++) {
                mn = min(mn,a[i]);
                mx = max(mx,a[i]);
            }
            if (mx-mn == abs(a[r]-a[l])) {
                res++;
                //if (l != r) cout << l << ' ' << r << '\n';
            }
        }
    }
    return res;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    first = true;
    ll ans = f(0,N-1);
    first = false;
    reverse(a,a+N);
    ans += f(0,N-1);
    cout << ans << '\n';
    //reverse(a,a+N);
    //cout << "brute: " << brute() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
