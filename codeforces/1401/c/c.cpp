#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        int mn = 1e9;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mn = min(mn,a[i]);
        }
        vector<int> b = a;
        sort(b.begin(),b.end());
        bool poss = true;
        for (int i = 0; i < n; i++) {
            if (a[i] == b[i]) continue;
            else if (a[i] % mn == 0 && b[i] % mn == 0) {
                continue;    
            }
            else {
                poss = false;
                break;
            }
        }
        cout << (poss?"YES":"NO") << '\n';
    }
}
