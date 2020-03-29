#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
string s, t;

vector<int> solve(string& s) {
    vector<int> ret;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1' && s[(i+1)%n] == '1') {
            s[i] = '0';
            s[(i+1)%n] = '0';
            ret.push_back(i);
        }
    }
    for (int i = 0; i < n; i++) {
        int c = i;
        while (s[c] == '1' && c >= 2 && s[c-1] == '0' && s[c-2] == '0') {
            s[c-2] = '1';
            s[c] = '0';
            ret.push_back(c-2);
            ret.push_back(c-1);
            c -= 2;
        }
        if (c > 0 && s[c] == '1' && s[c-1] == '1') {
            s[c] = s[c-1] = '0';
            ret.push_back(c-1);
        }
    }
    //handle odd case
    if (n&1) {
        while (true) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (s[i] == '1') cnt++;
            }
            if (cnt < 2) break;
            int r = n-1;
            for (; r >= 0; r--) {
                if (s[r] == '1') break;
            }
            while (s[(r+1)%n] != '1') {
                assert(s[(r+2)%n] == '0');
                s[r] = '0';
                s[(r+2)%n] = '1';
                ret.push_back((r+1)%n);
                ret.push_back(r);
                r = (r+2) % n;
            }
            s[r] = '0';
            s[(r+1)%n] = '0';
            ret.push_back(r);
        }
        //normalize again
        for (int i = 0; i < n; i++) {
            int c = i;
            while (s[c] == '1' && c >= 2 && s[c-1] == '0' && s[c-2] == '0') {
                s[c-2] = '1';
                s[c] = '0';
                ret.push_back(c-2);
                ret.push_back(c-1);
                c -= 2;
            }
            if (c > 0 && s[c] == '1' && s[c-1] == '1') {
                s[c] = s[c-1] = '0';
                ret.push_back(c-1);
            }
        }
    }
    //cout << s << '\n';
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> t;
    n = s.size();
    auto v1 = solve(s);
    auto v2 = solve(t);
    if (n&1) {
        if (s != t) {
            if (s[0] == '1') {
                for (int i = 1; i < n; i += 2) {
                    v1.push_back(i);
                }
                for (int i = 2; i < n; i += 2) {
                    v1.push_back(i);
                }
            }
            else if (t[0] == '1') {
                for (int i = 1; i < n; i += 2) {
                    v2.push_back(i);
                }
                for (int i = 2; i < n; i += 2) {
                    v2.push_back(i);
                }
            }
            else assert(false);
        }
    }
    //cout << s << '\n' << t << endl;
    //assert(s == t);
    reverse(v2.begin(),v2.end()); 
    assert(v1.size()+v2.size() <= 100000);
    cout << (v1.size()+v2.size()) << '\n';
    for (auto i: v1) {
        cout << i << '\n';
    }
    for (auto i: v2) {
        cout << i << '\n';
    }
}
