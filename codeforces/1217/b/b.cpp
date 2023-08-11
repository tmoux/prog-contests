#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, x; cin >> n >> x;
        vector<pair<int,int>> v;
        for (int i = 0; i < n; i++) {
            int d, h; cin >> d >> h;
            v.push_back({d,h});
        }
        int maxDelta = 0;
        int highest = 0;
        for (int i = 0; i < n; i++) {
            maxDelta = max(maxDelta,v[i].first-v[i].second);
            highest = max(highest,v[i].first);
        }
        if (highest >= x) {
            cout << 1 << '\n';
        }
        else if (maxDelta <= 0) {
            cout << "-1\n";
        }
        else {
            int numNeed = (x-highest+(maxDelta-1))/maxDelta;
            cout << (numNeed+1) << '\n';
        }
    }
}

