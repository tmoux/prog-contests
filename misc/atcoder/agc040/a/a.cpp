#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    vector<int> ans(n+1,0);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (s[i] == '<') {
            ans[i+1] = ans[i] + 1;
        }
    }
    for (int i = n; i >= 1; i--) {
        if (s[i-1] == '>') {
            ans[i-1] = max(ans[i-1],ans[i]+1);
        }
    }
    ll res = 0;
    for (int i: ans) {
        res += i;
        //cout << i << ' ';
    }
    //cout << '\n';
    cout << res << '\n';
}

