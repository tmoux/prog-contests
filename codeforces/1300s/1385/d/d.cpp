#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int solve(const string& s, int l, int r, char ch) {
    if (l == r) {
        return s[l] != ch;
    }
    int m = (l+r)/2;
    int first_half = 0;
    for (int i = l; i <= m; i++) first_half += s[i] != ch;
    int ans = first_half + solve(s,m+1,r,ch+1);

    int second_half = 0;
    for (int i = m+1; i <= r; i++) second_half += s[i] != ch;
    ans = min(ans,second_half + solve(s,l,m,ch+1));

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        int ans = solve(s,0,n-1,'a');
        cout << ans << '\n';
    }
}
