#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool isSubSeq(const string& a, const string& b) {
    int pt = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[pt]) {
            pt++;
            if (pt == b.size()) return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s, t; cin >> s >> t;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        for (int j = i; j < s.size(); j++) {
            string c;
            for (int k = 0; k < s.size(); k++) {
                if (k < i || k > j) c += s[k];
            }
            //cout << c << ": " << isSubSeq(c,t) << ' ' << (j-i+1) << '\n';
            //cout << i << ' ' << j << '\n';
            if (isSubSeq(c,t)) ans = max(ans,j-i+1);
        }
    }
    cout << ans << '\n';
}

