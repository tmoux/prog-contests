#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll maxn = 1e5+5, M = 1e9+7;
const ll INV2 = 500000004;
ll N;
ll L[maxn], R[maxn], sqr[maxn];

template <typename T>
void add(T& a, T b) {
    a = (a + b) % M;
}

ll ch2(ll n) {
    return (1LL*n*(n-1)/2) % M;
}

ll getSum(ll l, ll r, ll* arr) {
    return (arr[l] - arr[r] + M) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("sprinklers.in","r",stdin); freopen("sprinklers.out","w",stdout);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        ll x, y; cin >> x >> y;
        L[y] = x;
        R[y] = x+1;
    }
    for (ll i = 1; i < N; i++) {
        L[i] = min(L[i],L[i-1]);            
    }
    for (ll i = N - 2; i >= 0; i--) {
        R[i] = max(R[i],R[i+1]);
    }
    for (ll i = N - 1; i >= 0; i--) {
        sqr[i] = ch2(R[i]);
        add(sqr[i],sqr[i+1]);
    }
    for (ll i = N - 2; i >= 0; i--) {
        add(R[i],R[i+1]);
    }

    /*
    for (ll i = N-1; i >= 0; i--) {
        cout << i << ": " << R[i] << ' ' << sqr[i] << '\n';
    }
    */

    ll ans = 0;
    ll n = 1;
    for (ll i = 0; i < N; i++) {
        //cout << i << ": " << L[i] << ' ' << R[i] << '\n';
        while (n < N && L[i] + 1 < R[n]) n++;
        ll l = n - i - 1;
        ll x = L[i];
        ll c1 = getSum(i+1,n,sqr);
        ll d1 = (1LL*l*x*x) % M;
        ll d2 = 1LL*x*((l-2*getSum(i+1,n,R)+2*M)%M)%M;
        ll c2 = (((d1+d2) % M) * INV2) % M;
        /*
        if (i == 0) {
            cout << c1 << '\n';
            cout << c2 << '\n';
        }
        */
        //ll r = (getSum(i+1,n,sqr) + (((1LL*l*x*x)%M + l - 2*getSum(i+1,n,R)*x)/2 + M) % M) % M;
        ll r = (c1 + c2) % M;
        //cout << i << ": " << r << '\n';
        add(ans,r);
    }
    cout << ans << '\n';
    
    

    return 0;
}

