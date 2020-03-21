#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    string s; cin >> s;
    int ans = 0;
    for (char c = 'z'; c > 'a'; c--) {
        while (true) {
            bool found = false;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] != c) continue;
                bool rem = false;
                if (i > 0 && s[i-1] == c-1) rem = true;
                if (i < s.size()-1 && s[i+1] == c-1) rem = true;
                if (rem) {
                    s = s.substr(0,i)+s.substr(i+1);
                    //O(n)!
                    found = true;
                    ans++;
                    break;
                }
            }
            if (!found) break;
        }
    }
    //worse case: abbbbbb....
    //O(100*100) = 10^4
    cout << ans << endl;
}
