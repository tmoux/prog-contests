#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxm = 205;
int n, m, k;
int dp[maxm][maxn];

struct Interval
{
    int se, en, di, cnt;
}, invls[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> invls[i].se >> invls[i].en >> invls[i].di >> invls[i].cnt;
    }

    return 0;
}

