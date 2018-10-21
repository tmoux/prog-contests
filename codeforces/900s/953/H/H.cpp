#include <iostream>
#include <algorithm>
#include <vector>
typedef long long ll;
using namespace std;
ll getTop(ll prefix[], ll n, ll size) {
    if (n == 0 || size == 0) return 0;
    if (n > size) return -999999999;
    return prefix[n-1];
}

const ll maxn = 200005;
ll redPrefix[maxn], orangePrefix[maxn], whitePrefix[maxn];
vector<ll> red, orange, white;
ll arr[maxn];
char firstchar;
int main()
{
    //freopen("input.in","r",stdin);
    ll n, k; cin >> n >> k;
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (ll i = 0; i < n; i++) {
        char c; cin >> c;
        if (i == 0) firstchar = c;
        switch (c) {
            case 'R':
            red.push_back(arr[i]);
            break;
            case 'O':
            orange.push_back(arr[i]);
            break;
            case 'W':
            white.push_back(arr[i]);
            break;
        }
    }
    if (orange.size() == 0) {
        cout << "-1\n";
        return 0;
    }
    sort(red.begin(),red.end(),greater<ll>());
    sort(orange.begin(),orange.end(),greater<ll>());
    sort(white.begin(),white.end(),greater<ll>());
    //calculate prefix sums
    for (ll i = 0; i < red.size(); i++) {
        if (i == 0) redPrefix[i] = red[i];
        else redPrefix[i] = red[i] + redPrefix[i-1];
    }
    for (ll i = 0; i < orange.size(); i++) {
        if (i == 0) orangePrefix[i] = orange[i];
        else orangePrefix[i] = orange[i] + orangePrefix[i-1];
    }
    for (ll i = 0; i < white.size(); i++) {
        if (i == 0) whitePrefix[i] = white[i];
        else whitePrefix[i] = white[i] + whitePrefix[i-1];
    }
    //try using just red and orange
    ll ans = -1;
    ll kk = 1;
    /*
    for (ll i = 0; i < orange.size(); i++) {
        cout << orange[i] << '\n';
    }
    */
    for (; kk <= k; kk++) {
        ll ttr = getTop(orangePrefix,kk,orange.size())+getTop(redPrefix,k-kk,red.size());
        ans = max(ans,ttr);
        //ut << ttr << '\n';
    }
    //now try using just white and orange
    kk = 1;
    for (; kk <= k; kk++) {
        ll ttr = getTop(orangePrefix,kk,orange.size())+getTop(whitePrefix,k-kk,white.size());
        ans = max(ans,ttr);
    }
    cout << ans << '\n';
}
