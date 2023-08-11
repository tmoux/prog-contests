#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n;
string s;

map<string,int> mp;

int contain(const string& r) {
    //1 if invalid, 0 if fine
    for (int i = 0; i < r.size(); i++) {
        for (int j = 1; i + 2*j < r.size(); j++) {
            if (r[i] == r[i+j] && r[i+j] == r[i+2*j]) return 0;
        }
    }
    return 1;
}

ll cnt(int len) {
    int res = 0;

    
    for (int i = 0; i < (1<<len); i++) {
        string r;
        for (int j = 0; j < len; j++) {
            if (i & (1<<j)) r += '1';
            else r += '0';
        }
        res += contain(r);
        //cout << r << ": " << mp[r] << '\n';
    }
    return res;

    for (int i = 0; i + len <= n; i++) {
        res += contain(s.substr(i,len));
    }
    //cout << len << ": " << res << '\n';
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> s;
    n = s.size();
    for (int i = 1; i <= 20; i++) {
        cout << i << ": " << cnt(i) << endl;
    }
}

