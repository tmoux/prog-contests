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
        for (int j = 0; j < x; j++) {
            if (i+j > n) break;
            currMax = max(currMax,A[i+j]);
            currTot += A[i+j];
            if (currTot % 2 == 0 && currTot >= 2*currMax) {
                res++;
                //cout << i << ' ' << (i+j) << '\n';
            }
        }
    }
    /*
    cout << res << '\n';
    for (int i = 1; i <= n; i++) {
        cout << pfx[i] << ' ';
    }
    cout << '\n';
    cout << "odds: \n";
    for (int i = 1; i <= n; i++) {
        cout << odd[i] << ' ';
    }
    cout << '\n';
    */
    ll res2 = 0;
    for (int i = 1; i <= n; i++) {
        if (i+x-1 >= n) continue;
        /*
        if (i == 5) {
            cout << A[i-1] << '\n';
        }
        */
        if (pfx[i-1] % 2 == 0) {
            //cout << i << ' ' << even[n] - even[i+x-1] << '\n';
            res2 += even[n] - even[i+x-1];
        }
        else { 
            res2 += odd[n] - odd[i+x-1];
            //cout << i << ' ' << odd[n] - odd[i+x-1] << '\n';
            /*
            if (i == 5) {
                cout << odd[n] << ' ' << odd[i+x-1] << '\n';
            }
            */
        }
    }
    cout << res + res2 << '\n';
    

    return 0;
}

