#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5, x = 64;
int n, A[maxn], odd[maxn], even[maxn], pfx[maxn];

int popcount(ll x) {
    int res = 0;
    while (x) {
        if (x&1) res++;
        x >>= 1;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        ll ai; cin >> ai;
        A[i] = popcount(ai);
        pfx[i] = pfx[i-1] + A[i];
    }
    for (int i = 1; i <= n; i++) {
        odd[i] = odd[i-1] + (pfx[i] % 2 ? 1 : 0);
        even[i] = even[i-1] + (pfx[i] % 2 ? 0 : 1);
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        int currMax = 0;
        int currTot = 0;
        int c = 0;
        for (int j = 0; j <= n; j++) {
            if (i+j > n) break;
            currMax = max(currMax,A[i+j]);
            currTot += A[i+j];
            if (currTot % 2 == 0 && currTot >= 2*currMax) {
                res++;
                c++;
                //cout << i << ' ' << (i+j) << '\n';
            }
        }
        //cout << i << ' ' << c << '\n';
    }
    cout << res << '\n';

    return 0;
}

