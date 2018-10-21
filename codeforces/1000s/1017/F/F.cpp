#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e8+8;
const ll M = (1LL << 32);
int n, A, B, C, D;
inline ll f(ll x) { return ((1LL*A*(x*(x*x)%M)%M)%M+(B*x*x)%M+C*x+D)%M; }
bitset<maxn/3> sieve;
ll ans = 0;
inline int convert(int x) { //converts num to index in sieve
    if ((x+1) % 6 == 0) {
        return 2*(x/6);
    }
    else if ((x-1) % 6 == 0) {
        return 2*((x-1)/6)-1;
    }
    return -1;
}

void addp(int i) {
    ll p = i;
    ll accum = 0;
    while (n/p > 0) {
        accum += (ll)(n)/p;
        p *= i;
    }
    ans = (ans + (accum*f(i)) % M) % M;
}

void fill_sieve() {
    for (int i = 3; i <= n; i+= 2) {
        if ((i != 3) && (convert(i) == -1 || sieve[convert(i)])) continue;
        addp(i);
        for (ll j = 1LL*i*i; j <= n; j += 2*i) {
            int cj = convert(j);
            if (cj != -1 && cj < maxn/3) {
                sieve[cj] = true;
            }
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    scanf("%d %d %d %d %d",&n,&A,&B,&C,&D);
    fill_sieve();
    addp(2);

    cout << ans << '\n';

    return 0;
}
	

