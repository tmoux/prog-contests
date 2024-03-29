#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a, b, k;

int ceil(int a, int b) {
    return (a+b-1)/b;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a >> b >> k;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int hi; cin >> hi;
        int m = hi % (a+b);
        if (0 < m && m <= a) {
            v.push_back(0);
        }
        else {
            if (m == 0) {
                v.push_back(ceil(b,a));
            }
            else {
                assert(m > a);
                v.push_back(ceil(m-a,a));
            }
        }
    }
    sort(v.begin(),v.end());
    int tot = 0;
    int ans = 0;
    for (auto i: v) {
        if (tot + i > k) break;
        tot += i;
        ans++;
    }
    cout << ans << '\n';
}

