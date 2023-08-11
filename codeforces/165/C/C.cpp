#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
int pre[maxn];
int k, n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //read input
    cin >> k;
    string t; cin >> t;
    n = t.size();
    for (int i = 1; i <= n; i++) {
        if (t[i-1] == '1') pre[i] = 1;
        pre[i] += pre[i-1];
    }
    //calc answer
    ll ans = 0;
    for (int i = 1; i <= n; i++) 
        ans += (ll)(distance(lower_bound(pre+i,pre+1+n,k+pre[i-1]),upper_bound(pre+i,pre+1+n,k+pre[i-1])));
    cout << ans << '\n';
    return 0;
}
	

