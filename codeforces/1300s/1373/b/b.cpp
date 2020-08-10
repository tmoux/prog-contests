#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int turn = 0;
        while (true) {
            int idx = -1;
            for (int i = 0; i < (int)(s.size())-1; i++) {
                if (s[i] != s[i+1]) {
                    idx = i;
                    break;
                }
            }
            if (idx == -1) {
                cout << (turn?"DA":"NET") << '\n';
                break;
            }
            else {
                s.erase(idx,2);
                turn ^= 1;
            }
            //cout << turn << ": " << s << endl;
        }
    }
}
