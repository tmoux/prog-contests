#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        vector<int> len;
        int c0 = 0, c1 = 0;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            for (char c: s) {
                if (c == '0') c0++;
                else c1++;
            }
            len.push_back(s.size());
        }
        sort(len.begin(),len.end());
        int ans = 0;
        for (int i = n; i >= 0; i--) {
            int pairs = c0/2 + c1/2;
            int need = 0;
            int odds = 0;
            for (int j = 0; j < i; j++) {
                need += len[j]/2;
                if (len[j]&1) odds++;
            }
            if (pairs >= need) {
                int left = (c0+c1)-need*2;
                if (left >= odds) {
                    cout << i << '\n';
                    break;
                }
            }
        }
    }
}

