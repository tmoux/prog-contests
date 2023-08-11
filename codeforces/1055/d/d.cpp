#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
int n;
string pre[maxn], post[maxn];

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pre[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> post[i];
    }
    int len = 0;
    string match, replace;
    //find longest string and replace it
    for (int i = 0; i < n; i++) {
        int l = -1, r = -1;
        for (int j = 0; j < pre[i].size(); j++) {
            if (pre[i][j] != post[i][j]) {
                l = j;
                break;
            }
        }
        for (int j = pre[i].size()-1; j >= 0; j--) {
            if (pre[i][j] != post[i][j]) {
                r = j;
                break;
            }
        }
        if (l == -1) continue;
        else {
            int ourLen = r-l+1;
            if (ourLen > len) {
                len = ourLen;
                match = pre[i].substr(l,r-l+1);
                replace = post[i].substr(l,r-l+1);
            }
        }
    }
    /*
    cout << len << '\n';
    cout << match.size() << ' ' << match << '\n';
    cout << replace.size() << ' ' << replace << '\n';
    */
    if (len == 0) {
        assert(false);
        //should not be possible
    }
    for (int i = 0; i < n; i++) {
        string s = match + "#" + pre[i];
        auto z = z_function(s);
        for (int j = match.size()+1; j < z.size(); j++) {
            if (z[j] == len) {
                for (int k = j-match.size()-1, l = 0; l < replace.size(); k++, l++) {
                    pre[i][k] = replace[l];
                }
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << pre[i] << '\n' << post[i] << '\n';
        if (pre[i] != post[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    cout << match << '\n';
    cout << replace << '\n';
}

