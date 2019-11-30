#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    set<int> cur;
    set<int> day;
    int d = 0;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        //cout << i << ' ' << d << '\n';
        d++;
        if (a[i] > 0) {
            if (day.count(a[i])) {
                cout << -1 << '\n';
                return 0;
            }
            else {
                cur.insert(a[i]);
                day.insert(a[i]);
            }
        }
        else {
            a[i] *= -1;
            if (!cur.count(a[i])) {
                cout << -1 << '\n';
                return 0;
            }
            else {
                cur.erase(a[i]);
            }
        }
        if (cur.empty()) {
            ans.push_back(d);
            day.clear();
            d = 0;
        }
    }
    if (ans.empty() || !cur.empty()) {
        cout << -1 << '\n';
    }
    else {
        cout << ans.size() << '\n';
        for (int i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

