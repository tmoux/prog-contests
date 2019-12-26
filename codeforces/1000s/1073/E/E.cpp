#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 998244353;
//cnt[pos][div][started][mask]

ll l, r;
int k;

int d[20];
ll cnt[20][2][1<<10];
ll acc[20][2][1<<10];
ll sum = 0;
ll pow10[20];

ll CNT(int i, int div, int mask) {
    if (__builtin_popcount(mask) > k) return 0;
    int start = __builtin_popcount(mask) > 0;
    if (i < 0) return start?1:0;
    ll& res = cnt[i][div][mask];
    if (res != -1) return res;
    res = 0;
    int is;
    ll& accum = acc[i][div][mask];
    if (!div) {
        for (int dig = 0; dig < d[i]; dig++) {
            is = start?1:dig!=0;
            ll add = CNT(i-1,1,is?(mask|(1<<dig)):mask);
            res = (res + add) % M;

            accum += ((pow10[i]*dig)%M*add) % M;
            accum %= M;
            if (i > 0) accum += acc[i-1][1][is?(mask|(1<<dig)):mask];
            accum %= M;
        }
        is = start?1:d[i]!=0;
        ll add = CNT(i-1,0,mask|(1<<d[i]));
        res = (res + add) % M;

        accum += ((pow10[i]*d[i])%M*add) % M;
        accum %= M;
        if (i > 0) accum += acc[i-1][1][mask|(1<<d[i])];
        accum %= M;
    }
    else {
        for (int dig = 0; dig <= 9; dig++) {
            is = start?1:dig!=0;
            ll add = CNT(i-1,1,is?(mask|(1<<dig)):mask);
            res = (res + add) % M;

            accum += ((pow10[i]*dig)%M*add) % M;
            accum %= M;
            if (i > 0) accum += acc[i-1][1][is?(mask|(1<<dig)):mask];
            accum %= M;
        }
    }
    printf("[%d][%d][%d]: %d\n",i,div,mask,res);
    cout << "accum = " << accum << endl;
    return res;
}

int brute(int x) {
    int res = 0;
    for (int i = 1; i <= x; i++) {
        set<int> digits;
        int cp = i;
        while (cp > 0) {
            digits.insert(cp%10);
            cp /= 10;
        }
        if (digits.size() <= k) res++;
    }
    return res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> l >> r >> k;
    l--;
    pow10[0] = 1;
    for (int i = 1; i < 20; i++) {
        pow10[i] = (pow10[i-1] * 10) % M;
    }
    int pt = 0;
    ll cp = r;
    while (cp > 0) {
        d[pt++] = cp % 10;
        cp /= 10;
    }
    memset(cnt,-1,sizeof cnt);
    cout << r << ": " << CNT(pt-1,0,0) << ' ' << brute(r) << endl;
    //CNT(pt-1,0,0);
    ll R = sum;
    cout << "R = " << R << endl;

    /*
    sum = 0;
    pt = 0;
    cp = l;
    while (cp > 0) {
        d[pt++] = cp % 10;
        cp /= 10;
    }
    memset(cnt,-1,sizeof cnt);
    CNT(pt-1,0,0);
    ll L = sum;
    cout << "L = " << L << endl;

    cout << (R-L+M)%M << endl;
    */

    return 0;
}
