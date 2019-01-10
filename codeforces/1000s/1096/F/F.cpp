#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

const int M = 998244353;
const int maxn = 2e5+5;
int n, a[maxn];
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

int bit[maxn];
void add(int i, int x) {
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //long long when multiplying! Always!
    cin >> n;
    vector<int> vs;
    int missing = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == -1) {
            missing++;
        }
        else vs.push_back(a[i]);
    }
    sort(vs.begin(),vs.end());
    ll normalInversions = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] == -1) continue;
        (normalInversions += sum(a[i])) %= M;
        add(a[i],1);
    }
    if (missing == 0) {
        cout << normalInversions << '\n';
        return 0;
    }
    ll expMissing = (1LL*missing*((1LL*missing*(missing-1)/2)%M))%M;
    ll ans = ((1LL*normalInversions*2*missing) % M + expMissing) % M;
    int x = 0, y = missing;
    for (int i = 1; i <= n; i++) {
        if (a[i] != -1) {
            add(a[i],1);    
            auto it = lower_bound(vs.begin(),vs.end(),a[i]);
            int numSmaller = distance(vs.begin(),it);
            int numBigger = vs.size() - numSmaller - 1;
            int p = (n-a[i]) - numBigger;
            int q = a[i] - 1 - numSmaller;
            ll adding = (2*(1LL*p*x+1LL*q*y)%M)%M;
            ans = (ans + adding) % M;
        }
        else {
            x++; y--;                        
        }
    }

    ll q = modexp(2*missing,M-2);
    cout << (ans*q)%M << '\n';
    return 0;
}

