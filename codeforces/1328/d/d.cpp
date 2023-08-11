#include <bits/stdc++.h>
using namespace std;
using ll = long long;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s.insert(a[i]);
    }
    if (s.size() == 1) {
        cout << 1 << '\n';
        for (int i = 0; i < n; i++) {
            cout << 1 << ' ';
        }
        cout << '\n';
        return;
    }
    int start = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == a[(i+1)%n]) {
            start = (i+1)%n;
            break;
        }
    }
    if (start == -1) {
        if (n&1) {
            cout << 3 << '\n';
            for (int i = 0; i < n; i++) {
                if (i == n-1) cout << 3;
                else if (i % 2 == 0) {
                    cout << 1 << ' ';
                }
                else {
                    cout << 2 << ' ';
                }
            }
            cout << '\n';
        }
        else {
            cout << 2 << '\n';
            for (int i = 0; i < n; i++) {
                cout << (i&1?2:1) << ' ';
            }
            cout << '\n';
        }
        return;
    }
    else {
        vector<int> ans(n);
        ans[start] = 1;
        //cout << "start = " << start << endl;
        for (int i = (start+1)%n; i != start; i = (i+1)%n) {
            if (a[i] == a[(i-1+n)%n]) {
                ans[i] = ans[(i-1+n)%n];
            }
            else {
                ans[i] = ans[(i-1+n)%n]==1?2:1;
            }
            //cout << i << ": " << ans[i] << endl;
        }
        cout << 2 << '\n';
        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
