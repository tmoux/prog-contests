#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string a, b; cin >> a >> b;
        vector<int> ans;
        int start = 0;
        bool inc = true;
        for (int i = n-1; i >= 0; i--) {
            char c = inc?a[start+i]:a[start-i];          
            int cc = c-'0';
            if (!inc) cc = 1-cc;
            char d = cc+'0';
            if (d == b[i]) continue;
            else {
                if (c == a[start]) {
                    ans.push_back(i+1);
                    start = inc?start+i:start-i;
                    inc = !inc;
                }
                else {
                    ans.push_back(1);
                    ans.push_back(i+1);
                    start = inc?start+i:start-i;
                    inc = !inc;
                }
            }
        }
        cout << ans.size() << ' ';
        for (int i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
