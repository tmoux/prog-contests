#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n), b(n), c(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        for (int i = 0; i < n; i++) cin >> c[i];
        auto diff = [&a,&b,&c](int i, vector<int> v) {
            if (find(v.begin(),v.end(),a[i]) == v.end()) return a[i];
            if (find(v.begin(),v.end(),b[i]) == v.end()) return b[i];
            if (find(v.begin(),v.end(),c[i]) == v.end()) return c[i];
        };
        vector<int> res = {a[0]};
        for (int i = 1; i < n; i++) {
            if (i == n-1) {
                res.push_back(diff(i,{res.back(),res[0]}));
            }
            else {
                res.push_back(diff(i,{res.back()}));
            }
        }
        for (int i = 0; i < n; i++) {
            cout << res[i] << ' ';
        }
        cout << '\n';
    }
}
