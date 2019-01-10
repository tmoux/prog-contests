#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m;

bool poss(ll t, vector<int> a) {
    int curr = n;
    while (a[curr] == 0) curr--;
    for (int i = 0; i < m; i++) {
        if (curr < 1) break;
        ll canTake = t - curr;
        if (canTake < 0) break;
        while (canTake >= a[curr]) {
            canTake -= a[curr];            
            curr--;
            if (curr < 1) break;
        }
        a[curr] -= canTake;
    }
    return curr == 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll lo = 0, hi = 1e18;
    while (lo + 1 < hi) {
        ll m = (lo+hi)>>1;
        if (poss(m,a)) {
            //can be done in m time
            hi = m;
        }
        else lo = m;
    }
    //ans is hi
    cout << hi << '\n';

    return 0;
}

