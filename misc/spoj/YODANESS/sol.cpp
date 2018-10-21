#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 30005;
int n, bit[maxn];
void add(int i, int x) {
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

void solve() {
    memset(bit,0,sizeof bit);
    cin >> n;
    map<string,int> mp;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        mp[s] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        int j = mp[s];
        ans += (sum(n)-sum(j-1));
        add(j,1);
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while (t--) solve();
    return 0;
}

