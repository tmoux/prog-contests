#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
const ll INF = 1LL<<60;
int N, a[maxn], b[maxn];

int dp[maxn][maxn][maxn];
bool canReach(int i, int j, int k) {
    int& res = dp[i][j][k];
    if (res >= 0) return res;
    if (k == 0) {
        return res = i == j;        
    }
    res = canReach(i,j,k-1);
    res |= canReach(i%k,j,k-1);
    return res;
}

bool poss(int k) {
    for (int i = 1; i <= N; i++) {
        if (!canReach(a[i],b[i],k)) return false;
    }
    return true;
}

ll tr[maxn][maxn];
ll trace(int i, int j) {
    if (tr[i][j] >= 0) return tr[i][j];
    if (!canReach(i,j,53)) return INF;
    if (i == j) return 0;
    tr[i][j] = 0;
    for (int k = 1; k < 53; k++) {
        if (canReach(i,j,k)) return tr[i][j] = (1LL<<k) + trace(i%k,j);
    }
    assert(false);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    memset(dp,-1,sizeof dp);
    memset(tr,-1,sizeof tr);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> b[i];
    }
    if (!poss(53)) {
        cout << -1 << '\n';
        return 0;
    }
    ll ans = 0;
    for (int k = 53; k > 0; k--) {
        //cout << (k-1) << ": " << poss(k-1) << '\n';
        if (poss(k-1)) {
            continue;
        }
        else {
            ans += (1LL<<k);
            //cout << "adding " << k << ", " << (1LL<<k) << '\n';
            for (int i = 1; i <= N; i++) {
                if (trace(a[i]%k,b[i]) <= trace(a[i],b[i])) {
                    a[i] %= k;
                }
                else {
                    continue;
                }
            }
            /*
            for (int i = 1; i <= N; i++) {
                cout << a[i] << ' ';
            }
            cout << "\n";
            */
        }
    }
    cout << ans << '\n';
}
