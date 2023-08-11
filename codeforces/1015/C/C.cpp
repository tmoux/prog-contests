#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    ll tot = 0, least = 0;
    vector<ll> diffs;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        tot += a;
        least += b;
        diffs.push_back(a-b);
    }
    if (least > m) {
        cout << -1 << '\n';
        return 0;
    }
    //now we know it's possible
    sort(diffs.begin(),diffs.end(),greater<ll>());
    int ans = 0;
    int idx = 0;
    while (tot > m) {
        ans++;
        tot -= diffs[idx++];
    }

    cout << ans << '\n';

    return 0;
}
	

