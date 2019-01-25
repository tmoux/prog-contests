#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
string s;

char getDiff(char a, char c) {
    if (a != 'R' && c != 'R') return 'R';
    if (a != 'B' && c != 'B') return 'B';
    if (a != 'G' && c != 'G') return 'G';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    s = '#' + s + '#';
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == s[i-1]) {
            s[i] = getDiff(s[i-1],s[i+1]);
            ans++;
        }
    }
    cout << ans << '\n';
    cout << s.substr(1,n) << '\n';


    return 0;
}

