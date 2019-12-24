#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, m, q;
ll a[maxn];
int cnt[maxn];
int ans[maxn];

int bit[maxn];
void add(int i, int x) {
    i++;
    for (; i <= m; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    i++;
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

vector<int> v[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        ai--;
        cnt[ai]++;
    }
    int mx = 0;
    for (int i = 0; i < m; i++) {
        mx = max(mx,cnt[i]);
        a[cnt[i]+1]++;
        v[cnt[i]+1].push_back(i);
    }
    for (int i = 1; i <= mx; i++) {
        a[i] += a[i-1];
    }
    for (int i = 1; i <= mx; i++) {
        a[i] += a[i-1];
    }
    vector<pair<ll,int>> queries;
    for (int i = 0; i < q; i++) {
        ll k; cin >> k;
        k -= n+1;
        queries.push_back({k,i});
    }
    sort(queries.begin(),queries.end(),greater<pair<ll,int>>());
    ll tot = a[mx];
    int cur = mx;
    for (int i = 0; i < m; i++) {
        if (cnt[i] < mx) add(i,1);
    }
    for (auto p: queries) {
        ll k = p.first;
        if (k >= tot) {
            k -= tot;
            ans[p.second] = k % m;
        }
        else {
            while (k < (cur==0?0:a[cur-1])) {
                for (int i: v[cur]) {
                    add(i,-1);
                }
                cur--;
            }
            k -= cur==0?0:a[cur-1];
            //find k'th # in bit
            int lo = -1, hi = m;
            while (lo + 1 < hi) {
                int mid = (lo+hi)/2;
                if (sum(mid) >= (k+1)) {
                    hi = mid;
                }
                else lo = mid;
            }
            ans[p.second] = hi;
            /*
            cout << p.second << ": " << hi << endl;
            cout << "cur = " << cur << endl;
            cout << "k = " << k << ", a[cur] = " << a[cur] << endl;
            */
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i]+1 << '\n';
    }
}
