#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, x, y; cin >> n >> x >> y;
        int ans = 2e9;
        vector<int> ret;
        for (int i = 1; i <= y-x; i++) {
            if ((y-x)%i == 0) {
                vector<int> v;
                for (int j = x; j <= y; j += i) {
                    v.push_back(j);
                }
                for (int j = x-i; j > 0 && v.size() < n; j -= i) {
                    v.push_back(j);
                }
                for (int j = y+i; v.size() < n; j += i) {
                    v.push_back(j);
                }
                if (v.size() == n) {
                    sort(v.begin(),v.end());
                    if (v.back() < ans) {
                        ans = v.back();
                        ret = v;
                    }
                }
            }
        }
        for (auto i: ret) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
