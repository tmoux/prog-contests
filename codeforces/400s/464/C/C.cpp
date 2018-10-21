#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
const ll maxn = 100005;
ll n;
string s;
pair<ll,string> queries[maxn];
ll len[10], val[10];

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x % MOD;
    if (n % 2 == 0) return modexp(x*x % MOD, n/2);
    if (n % 2 == 1) return (x * modexp(x*x % MOD, n/2)) % MOD;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> n;
    for (int i = 1; i <= n; i++) {
        string a; cin >> a;
        string t1 = a.substr(0,1);
        char t = t1[0];
        string t2 = a.substr(3);
        ll d = t - '0';
        queries[i] = {d,t2};
    }
    queries[0] = {0,s};
    //modify len, val starting from the back
    for (ll i = 0; i < 10; i++) {
        len[i] = 1;
        val[i] = i;
    }
    for (int i = n; i >= 0; i--) {
        ll newlen = 0;
        ll newval = 0;
        ll d = queries[i].first;
        for (int j = queries[i].second.size() - 1; j >= 0; j--) {
            ll f = queries[i].second[j] - '0'; 
            newval = (newval + modexp(10,newlen)*val[f]) % MOD;
            newlen = (newlen + len[f]) % (MOD-1);
        }
        val[d] = newval;
        len[d] = newlen;
        /*
        for (int i = 0; i < 10; i++) {
            cout << i << ' ' << val[i] << ' ' << len[i] << '\n';
        }
        */
    }
    cout << val[0] << '\n';
    return 0;
}
	

