#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
const int maxn = 5005;
int n, a[maxn];

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

ll modInverse(ll x) {
    return modexp(x,M-2);
}

void madd(int& a, int b) {
    a = (a+b) % M;
}


int dp[maxn][maxn]; //dp[i][j], i = current, j = total # cards

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<int,int> mp;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        
    }
    sort(a+1,a+n+1);


    return 0;
}

