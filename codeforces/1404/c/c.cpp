#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, q;
int a[maxn];

struct Fenwick
{
    int n;
    vector<int> bit;
    Fenwick(int n_) {
        n = n_;
        bit.resize(n+1,0);
    }
    void add(int i, int x) {
        for (; i <= n; i += i & (-i))
            bit[i] += x;
    }

    int sum(int i) {
        int r = 0;
        for (; i; i -= i & (-i)) {
            r += bit[i];
        }
        return r;
    }
};

vector<pair<int,int>> queries[maxn];
int ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = i-a[i];
        //cout << a[i] << ' ';
    }
    //cout << '\n';
    for (int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        int l = x + 1;
        int r = n - y;
        queries[r].push_back({l,i});
    }

    Fenwick cnt(n);
    for (int i = 1; i <= n; i++) {
        if (a[i] < 0 || a[i] > cnt.sum(1)) {}
        else {
            int lo = 1, hi = i+1;
            while (lo + 1 < hi) {
                int mid = (lo+hi)/2;
                if (a[i] <= cnt.sum(mid)) {
                    lo = mid;
                }
                else {
                    hi = mid;
                }
            }
            cnt.add(1,1);
            if (hi <= n) cnt.add(hi,-1);
        }
        /*
        cout << i << ": ";
        for (int j = 1; j <= n; j++) {
            cout << cnt.sum(j) << ' ';
        }
        cout << '\n';
        */
        for (auto p: queries[i]) {
            int l = p.first;
            int id = p.second;
            ans[id] = cnt.sum(l);
            //cout << l << ' ' << i << ": " << ans[id] << endl;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}
