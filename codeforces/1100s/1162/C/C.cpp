#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, k;
int x[maxn];

bool seen[maxn];
vector<int> s[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        cin >> x[i];
        seen[x[i]] = true;
        s[x[i]].push_back(i);
    }
    int ans = 3*n-2;
    for (int i = 1; i <= n; i++) {
        for (int j = i-1; j <= i+1; j++) {
            if (j < 1 || j > n) continue;
            if (!seen[i] || !seen[j]) continue;
            if (*s[i].begin() <= s[j].back()) ans--;    
        }
    }
    cout << ans << '\n';
}

