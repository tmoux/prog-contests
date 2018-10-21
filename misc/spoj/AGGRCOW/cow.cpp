#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, c, x[maxn];

bool poss(int dist) {
    int prev = -1e9;
    int cows = 0;
    for (int i = 0; i < n; i++) {
        if (prev + dist <= x[i]) {
            cows++;
            prev = x[i];
        }
    }
    return cows >= c;
}

void solve() {
    cin >> n >> c;
    for (int i = 0; i < n; i++) cin >> x[i];
    sort(x,x+n);
    int lo = 0, hi = 1e9+5;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (poss(mid)) {
            lo = mid;
        }
        else hi = mid;
    }
    cout << lo << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();

    return 0;
}
	

