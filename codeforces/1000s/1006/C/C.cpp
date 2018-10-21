#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n;
ll pre[maxn];
vector<ll> rev;

int getr(ll f) {
    auto it = lower_bound(rev.begin(),rev.end(),f);
    if (it == rev.end()) return -1;
    if (*it != f) return -1;
    int dist = (int)(distance(rev.begin(),it));
    return n - dist + 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pre[i];
        pre[i] += pre[i-1];
    }
    for (int i = n; i >= 1; i--) {
        rev.push_back(pre[n] - pre[i]);    
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll f = pre[i];
        int r = getr(f);
        //cout << i << ' ' << r << '\n';
        if (r == -1) continue;
        if (r <= i) break;
        ans = f;
    }
    cout << ans << '\n';
    //cout << getr(5) << '\n';

    return 0;
}
	

