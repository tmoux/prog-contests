#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

const int maxn = 1e6+6;
int n, a[maxn];
vector<int> v[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    set<int> s;
    ll curr = 0;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        v[a[i]].push_back(i);
        s.insert(a[i]);
        curr += s.size();
    }
    ans += curr;
    for (int i = 2; i <= n; i++) {
        if (a[i] != a[i-1]) {
            curr -= n-i+1;
            curr += i-1;
            auto it = upper_bound(all(v[a[i-1]]),i);
            if (it != v[a[i-1]].end()) {
                curr += n-*it+1;
            }
            it = lower_bound(all(v[a[i]]),i);
            if (it != v[a[i]].begin()) {
                --it;
                curr -= *it;
            }
        }
        ans += curr;
    }
    double res = ans/(double)(1LL*n*n);
    cout << fixed << setprecision(10) << res << '\n';
}

