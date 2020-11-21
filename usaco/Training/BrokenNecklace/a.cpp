/*
ID: silxikys
LANG: C++
TASK: beads
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int cnt(string s, char a, char b) {
    int ans = 0;
    for (int l = 0; l < s.size() && (s[l] == 'w' || s[l] == a); ans++, l++) {}
    for (int r = s.size()-1; r >= 0 && (s[r] == 'w' || s[r] == b); ans++, r--) {}
    return min(ans,(int)s.size());
}

int main() {
    freopen("beads.in","r",stdin);
    freopen("beads.out","w",stdout);
    int N; cin >> N;
    string s; cin >> s;
    s += s;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        string t = s.substr(i,N);
        ans = max(ans,cnt(t,'r','r'));
        ans = max(ans,cnt(t,'r','b'));
        ans = max(ans,cnt(t,'b','r'));
        ans = max(ans,cnt(t,'b','b'));
    }
    cout << ans << '\n';
}
