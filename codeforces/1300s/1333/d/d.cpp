#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
int n, k;
string s;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    cin >> s;
    vector<vector<int>> ans;
    while (true) {
        vector<int> v;
        for (int i = 0; i < n-1; i++) {
            if (s[i] == 'R' && s[i+1] == 'L') {
                v.push_back(i);
            }
        }
        if (v.empty()) break;
        ans.push_back(v);
        for (auto i: v) {
            swap(s[i],s[i+1]);
        }
    }
    int mn = ans.size();
    int mx = 0;
    for (auto& v: ans) mx += v.size();
    if (k < mn || k > mx) {
        cout << -1 << '\n';
        return 0;
    }
    int extra = k-mn;
    for (auto v: ans) {
        while (extra > 0 && v.size() > 1) {
            cout << 1 << ' ' << (v.back()+1) << '\n';
            v.pop_back();
            extra--;
        }
        cout << v.size() << ' ';
        for (auto i: v) {
            cout << i+1 << ' ';
        }
        cout << '\n';
    }
}
