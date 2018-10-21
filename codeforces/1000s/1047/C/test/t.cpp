#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5, maxx = 25000000;
int n, A[maxn], prime[maxx], cnt[maxx];

void sieve() {
    for (ll i = 2; i < maxx; i++) {
        if (!prime[i]) {
            prime[i] = i;
            for (ll j = i*i; j < maxx; j += i) {
                prime[j] = i;
            }
        }
    }
}

void countPrimes(int i) {
    if (i == 1) return;
    cnt[prime[i]]++;
    int p = prime[i];
    while (i % p == 0) i /= p;
    countPrimes(i);
}

void getmax(int i, int& maxOcc) {
    if (i == 1) return;
    maxOcc = max(maxOcc,cnt[prime[i]]);
    int p = prime[i];
    while (i % p == 0) i /= p;
    getmax(i,maxOcc);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int gc = 0;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        gc = __gcd(gc,A[i]);
    }
    for (int i = 0; i < n; i++) {
        A[i] /= gc;
    }
    sieve();
    for (int i = 0; i < n; i++) {
        countPrimes(A[i]);    
    }
    int maxOcc = 0;
    for (int i = 0; i < n; i++) {
        getmax(A[i],maxOcc);        
    }
    int res = n-maxOcc;
    cout << (res == n ? -1 : res) << '\n';
}
