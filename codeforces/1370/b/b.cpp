#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(2*n);
        int sum = 0;
        vector<int> even, odd;
        for (int i = 0; i < 2*n; i++) {
            cin >> a[i];
            a[i] %= 2;
            sum = (sum+a[i]) % 2;
            if (a[i] % 2 == 0) {
                even.push_back(i);
            }
            else {
                odd.push_back(i);
            }
        }
        if (sum % 2 == 0) {
            if (!even.empty()) {
                even.pop_back();
                even.pop_back();
            }
            else {
                odd.pop_back();
                odd.pop_back();
            }
        }
        else {
            even.pop_back();
            odd.pop_back();
        }
        assert(even.size() % 2 == 0 && odd.size() % 2 == 0);
        while (!even.empty()) {
            int x = even.back();
            even.pop_back();
            int y = even.back();
            even.pop_back();
            cout << x+1 << ' ' << y+1 << '\n';
        }
        while (!odd.empty()) {
            int x = odd.back();
            odd.pop_back();
            int y = odd.back();
            odd.pop_back();
            cout << x+1 << ' ' << y+1 << '\n';
        }
    }
}
