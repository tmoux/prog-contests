#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 705;
int n, A[maxn];
int gc[maxn][maxn];
bool dp[maxn][maxn][maxn], seen[maxn][maxn][maxn];

int gcd(int a, int b) {
    if (a == 0 || b == 0) return 5;
    return gc[a][b];
}

bool work(int prev, int l, int r) {
    if (seen[prev][l][r]) return dp[prev][l][r];
    seen[prev][l][r] = true;
    if (r < l) return dp[prev][l][r] = true;
    if (l == r) return dp[prev][l][r] = gcd(l,prev) != 1;
    bool poss = false;
    for (int i = l; i <= r; i++) {
        if (gcd(prev,i) != 1 && work(i,l,i-1) && work(i,i+1,r)) {
            poss = true;
            break;
        }
    }
    //cout << prev << ' ' << l << ' ' << r << ' ' << poss << '\n';
    return dp[prev][l][r] = poss;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            gc[i][j] = __gcd(A[i],A[j]);
        }
    }
    bool ans = work(0,1,n);
    cout << (ans ? "Yes" : "No") << '\n';

    return 0;
}
