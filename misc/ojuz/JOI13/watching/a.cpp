#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
const int maxp = 1e5+5;
int pos[maxn];
int N, P, Q;

int dp[maxn][maxn]; //i'th position, # bigs used
//= min # small used
bool poss(int w) {
    memset(dp,-1,sizeof dp);

}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> P >> Q;
    for (int i = 0; i < N; i++) cin >> pos[i];
    sort(pos,pos+N);
    int lo = 0, hi = 1e9+5;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (poss(mid)) {
            hi = mid;
        }
        else lo = mid;
    }
    cout << hi << '\n';
}

