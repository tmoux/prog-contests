#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxx = 5000005;
int spf[maxx], numPrimeFactors[maxx];
void sieve() {
    spf[1] = 1;
    for (int i = 2; i < maxx; i++) spf[i] = i;
    for (int i = 4; i < maxx; i+=2) spf[i] = 2;
    for (int i = 3; i*i < maxx; i++) {
        if (spf[i] == i) {
            for (int j = i*i; j < maxx; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

int pfx[maxx];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    sieve();
    for (int i = 2; i < maxx; i++) {
        if (spf[i] == i) numPrimeFactors[i] = 1;
        else numPrimeFactors[i] = 1 + numPrimeFactors[i/spf[i]];
    }
    for (int i = 2; i < maxx; i++) {
        pfx[i] = pfx[i-1] + numPrimeFactors[i];
    }
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        int ans = pfx[a] - pfx[b];
        cout << ans << '\n';
    }

    return 0;
}

