#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;
const int maxn = 1e5+5;
int ans[maxn];

void solve(int l, int r) {
    for (int i = l; i < r; i++) {
        if (s[i] == 'L' && s[i+1] == 'R') {
            solve(l,i);
            solve(i+1,r);
            return;
        }
    }
    int split = l;
    for (int i = l; i < r; i++) {
        if (s[i] == 'R' && s[i+1] == 'L') {
            split = i;
            break;
        }
    }
    int t = 0;
    for (int i = split; i >= l; i--, t^=1) {
        if (t == 0) ans[split]++;
        else ans[split+1]++;
    }
    t = 1;
    for (int i = split + 1; i <= r; i++, t^=1) {
        if (t == 0) ans[split]++;
        else ans[split+1]++;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    int n = s.size();
    s = '#' + s;
    solve(1,n);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

