#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, k[maxn];
vector<int> sales[maxn];

int a[maxn];

bool poss(int x) {
    //buy sales greedily, buy remaining on x'th day
    for (int i = 1; i <= n; i++) a[i] = k[i];
    vector<int> last(n+1,0);
    for (int i = 1; i <= min(200000,x); i++) {
        for (int t: sales[i]) {
            last[t] = i;
        }
    }
    vector<vector<int>> use(x+1);
    for (int i = 1; i <= n; i++) {
        if (last[i] > 0) use[last[i]].push_back(i);
    }
    int curr = 0;
    for (int i = 1; i <= x; i++) {
        curr++;
        for (int t: use[i]) {
            int mn = min(a[t],curr);
            curr -= mn;
            a[t] -= mn;
        }
    }
    int left = 0;
    for (int i = 1; i <= n; i++) left += a[i];
    return curr >= 2*left;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> k[i];
    for (int i = 0; i < m; i++) {
        int d, t; cin >> d >> t;
        sales[d].push_back(t);
    }
    int lo = 0, hi = maxn*2;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (poss(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << '\n';
}

