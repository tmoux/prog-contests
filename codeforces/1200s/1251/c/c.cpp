#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        vector<int> even, odd;
        for (char c: s) {
            if ((c-'0') % 2 == 0) {
                even.push_back(c-'0');
            }
            else {
                odd.push_back(c-'0');
            }
        }
        reverse(even.begin(),even.end());
        reverse(odd.begin(),odd.end());
        vector<int> ans;
        while (!even.empty() || !odd.empty()) {
            if (even.empty()) {
                ans.push_back(odd.back());
                odd.pop_back();
            }
            else if (odd.empty()) {
                ans.push_back(even.back());
                even.pop_back();
            }
            else {
                if (odd.back() < even.back()) {
                    ans.push_back(odd.back());
                    odd.pop_back();
                }
                else {
                    ans.push_back(even.back());
                    even.pop_back();
                }
            }
        }
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
        }
        cout << '\n';
    }
}

