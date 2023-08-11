#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        vector<int> pos;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            int li; cin >> li;
            if (li == 0) {
                pos.push_back(i);
                v.push_back(a[i]);
            }
        }
        sort(v.begin(),v.end(),greater<int>());
        for (int i = 0; i < pos.size(); i++) {
            a[pos[i]] = v[i];
        }
        for (auto i: a) {
            cout << i << ' ';
        }
        cout << '\n';
        /*
        vector<int> pfx(n);
        for (int i = 0; i < n; i++) {
            pfx[i] = a[i];
            if (i > 0) pfx[i] += pfx[i-1];
        }
        int ans = -1;
        for (int i = 0; i < n; i++) {
            if (pfx[i] < 0) {
                ans = i;
                break;
            }
        }
        cout << (ans+1) << '\n';
        */
    }
}
