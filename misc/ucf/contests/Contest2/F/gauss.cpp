#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
typedef long long ll;

int n;
ll A[30005];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    priority_queue<ll,vector<ll>,greater<ll>> q;
    for (int i = 0; i < n; i++) {
        ll a; cin >> a;
        q.push(a);
    }

    ll ans = 0;
    while (!q.empty()) {
        ll a1 = q.top();
        q.pop();
        ll a2 = q.top();
        q.pop();
        ans += a1+a2;
        if (q.size() == 0) break;
        else q.push(a1+a2);
    }
    cout << ans << '\n';

    return 0;
}
	

