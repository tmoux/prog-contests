#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, s, k;
        cin >> n >> s >> k;
        set<int> ss;
        while (k--) {
            int ai; cin >> ai;
            ss.insert(ai);
        }
        for (int i = 0; ; i++) {
            if (s+i <= n && !ss.count(s+i)) {
                cout << i << '\n';
                break;
            }
            if (s-i >= 1 && !ss.count(s-i)) {
                cout << i << '\n';
                break;
            }
        }
    }
}

