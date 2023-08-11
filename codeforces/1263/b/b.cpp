#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<string> a(n);
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            a[i] = s;
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            bool same = false;
            for (int j = i + 1; j < n; j++) {
                if (a[i] == a[j]) {
                    same = true;
                    break;
                }
            }
            if (same) {
                cnt++;
                //change 1st digit
                int ans = -1;
                for (int d = 0; d <= 9; d++) {
                    bool poss = true;
                    for (int j = 0; j < n; j++) {
                        if (a[j][0] == d+'0') {
                            poss = false;
                            break;
                        }
                    }
                    if (poss) {
                        ans = d;
                        break;
                    }
                }
                a[i][0] = ans+'0'; 
            }
        }
        cout << cnt << '\n';
        for (int i = 0; i < n; i++) {
            cout << a[i] << '\n';
        }
    }
}

