#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;

vector<int> v[maxn];

int ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        v[ai].push_back(i);
    }

    int cnt = 0;
    for (int i = 100000; i >= 1;) {
        if (v[i].empty()) {
            i--;
        }
        else {
            cnt++;
            for (int j = i; j >= 1; j--) {
                if (v[j].empty()) {
                    cout << -1 << '\n';
                    return 0;
                }
                ans[v[j].back()] = cnt;
                v[j].pop_back();
            }
        }
    }
    cout << cnt << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
