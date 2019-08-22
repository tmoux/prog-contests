#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005, oo = 2e9+9;
int N, Z, W;
int a[maxn];

int dp[2][maxn][maxn];

void amax(int& a, int b) {
    a = max(a,b);
}

void amin(int& a, int b) {
    a = min(a,b);
}

int mx[maxn][maxn], mn[maxn][maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Z >> W;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    if (N == 1) {
        cout << abs(a[1]-W) << '\n';
    }
    else {
        cout << max(abs(a[N]-W),abs(a[N]-a[N-1])) << '\n';
    }
}

