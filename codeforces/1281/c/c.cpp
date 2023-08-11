#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int x; cin >> x;
        string s; cin >> s;
        int i = 0;
        for (; i < x; i++) {
            int num = s[i]-'0';
            if (num == 1) continue;
            string b = s.substr(i+1);
            if (num == 2) {
                s += b;
            }
            else if (num == 3) {
                s += b+b;
            }
            //cout << s << endl;
            //cout << s.size() << endl;
            if (s.size() > x) break;
        }
        ll sz = s.size();
        i++;
        for (; i < x; i++) {
            int a = i+1;    
            int num = s[i]-'0';
            ll b = (sz - (i+1) + M) % M;
            sz = (a + 1LL*num*b) % M;
            //cout << i << ": " << sz << endl;
        }
        cout << sz << '\n';
    }
}

