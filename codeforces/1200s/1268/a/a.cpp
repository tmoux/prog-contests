#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
int d[maxn], ans[maxn];

set<int> diff;
bool good() {
    if (diff.empty()) return true;
    int i = *diff.begin();
    return ans[i] > d[i];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        d[i] = c-'0';
        ans[i] = 9;
        if (d[i] != ans[i]) {
            diff.insert(i);
        }
    }
    for (int i = 0; i < k; i++) {
        for (int dig = 0; dig <= 9; dig++) {
            for (int j = i; j < n; j += k) {
                ans[j] = dig;
                if (d[j] != ans[j]) {
                    diff.insert(j);
                }
                else if (diff.count(j)) diff.erase(j);
            }
            if (good()) break;
        }
    }
    assert(good());
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i];
    }
    cout << '\n';
}
