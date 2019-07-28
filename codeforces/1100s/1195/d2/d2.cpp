#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
const int maxn = 1e5+5;
int a[maxn];
int n;

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int madd(int& a, int b) {
    a = (a+b) % M;
}

int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res =  mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int e10[maxn];

int numdigits(int x) {
    int r = 0;
    while (x) {
        x /= 10;
        r++;
    }
    return r;
}

int len[maxn];
int cnt[15];
int num[15][15]; //num[pos][digit]

int dp[15][15][2];
int f(int l1, int l2, int type) {
    if (dp[l1][l2][type] != -1) return dp[l1][l2][type];
    //cout << l1 << ' ' << l2 << ' ' << type << endl;
    int c = -1;
    while (l1 > 0 || l2 > 0) {
        if (l2 > 0) {
            l2--;
            c++;
            if (type == 1 && l2 == 0) {
                return dp[l1][l2][type] = c;
            }
        }
        if (l1 > 0) {
            l1--;
            c++;
            if (type == 0 && l1 == 0) {
                return dp[l1][l2][type] = c;
            }
        }
    }
    assert(false);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    memset(dp,-1,sizeof dp);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        len[i] = numdigits(a[i]);
        cnt[len[i]]++;
    }
    for (int i = 0; i <= 25; i++) {
        e10[i] = modexp(10,i);
    }
    for (int i = 1; i <= n; i++) {
        int d = 0;
        while (a[i] > 0) {
            num[d][a[i]%10]++;
            a[i] /= 10;
            d++;
        }
    }
    int ans = 0;
    for (int curpos = 0; curpos <= 9; curpos++) {
        for (int digit = 1; digit <= 9; digit++) {
            int m = num[curpos][digit];
            if (m == 0) continue;
            //cout << curpos << ' ' << digit << ": " << m << '\n';
            for (int l2 = 1; l2 <= 10; l2++) {
                if (cnt[l2] == 0) continue;
                int a1 = mult(digit,e10[f(curpos+1,l2,0)]);
                a1 = mult(a1,m);
                a1 = mult(a1,cnt[l2]);
                int a2 = mult(digit,e10[f(l2,curpos+1,1)]);
                a2 = mult(a2,m);
                a2 = mult(a2,cnt[l2]);
                //cout << a1 << ' ' << a2 << '\n';
                madd(ans,a1);
                madd(ans,a2);
            }
        }
    }
    cout << ans << '\n';
}


