#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, sq = int(sqrt(maxn))+5, M = 1e9+7;
int n, q, a[maxn], block;
int freq[sq][maxn], pfx[sq], bucket[maxn], toFirst[sq];
ll xx[maxn], xxinv[maxn];

ll modexp(ll x, ll n, int M) {
    if (x == 0 && n == 0) return 1LL;
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2,M);
    return (x*modexp((x*x)%M,n/2,M))%M;
}

ll modInverse(ll x, int M) { return modexp(x,M-2,M);}

ll divide(ll curr, ll x, int M) {
    return (curr * xxinv[x+1]) % M;
}
ll multiply(ll curr, ll x, int M) {
    return (curr * xx[x+1]) % M;
}

int seen[maxn];

int main()
{
    scanf("%d %d",&n,&q);
    for (int i = 0; i < maxn; i++) {
        xx[i] = modexp(i,i,M);
        xxinv[i] = modInverse(xx[i],M);
    }
    block = (int)(sqrt(n));
    for (int i = 1; i <= n; i++) {
        bucket[i] = (i-1)/block + 1;
        if (i == n || bucket[i] != i/block + 1) {
            pfx[bucket[i]] = modexp(i+1,i+1,M);
            freq[bucket[i]][0] = i;
        }
        if (i == 1 || bucket[i] != bucket[i-1]) {
            toFirst[bucket[i]] = i;
        }
    }
    while (q--) {
        int t; scanf("%d",&t);
        if (t == 1) {
            int i, k; scanf("%d %d",&i,&k);
            int b = bucket[i];
            for (int j = b; j <= bucket[n]; j++) {
                pfx[j] = divide(pfx[j],freq[j][a[i]],M);
                freq[j][a[i]]--;
                pfx[j] = multiply(pfx[j],freq[j][a[i]],M);
            }
            a[i] = k;
            for (int j = b; j <= bucket[n]; j++) {
                pfx[j] = divide(pfx[j],freq[j][a[i]],M);
                freq[j][a[i]]++;
                pfx[j] = multiply(pfx[j],freq[j][a[i]],M);
            }
        }
        else {
            int p; scanf("%d",&p);
            int b = bucket[p];
            ll curr = b == 1 ? 1LL : pfx[b-1];
            int* f = freq[b-1];
            for (int i = toFirst[b]; i <= p; i++) {
                int x = a[i];
                int div = f[x] + seen[x];
                curr = divide(curr,div,M);
                seen[x]++;
                curr = multiply(curr,div+1,M);
            }
            for (int i = toFirst[b]; i <= p; i++) {
                seen[a[i]]--;
            }
            printf("%d\n",curr);
        }
    }
    return 0;
}

