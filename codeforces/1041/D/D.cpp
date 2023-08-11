#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, h, s[maxn], e[maxn];
int pfx[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> h;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> e[i];
        if (i != 0) {
            pfx[i] = pfx[i-1] + (s[i] - e[i-1]);
        }
        //cout << i << ' ' << pfx[i] << '\n';
    }
    int L = 0;
    int maxans = 0;
    for (int i = 0; i < n; i++) {
        while (L < n && pfx[i] + h > pfx[L]) L++;
        int start, land;
        if (pfx[L] - pfx[i] >= h) {
            start = s[i];
            land = s[L] - (pfx[L] - pfx[i] - h);
        }
        else {
            int leftToGo = h - (pfx[L-1] - pfx[i]);    
            //cout << i << ' ' << L << '\n';
            //cout << "leftToGo: " << leftToGo << '\n';
            start = s[i];
            land = e[L-1] + leftToGo;
        }
        maxans = max(maxans,land-start);
        //cout << i << ' ' << start << "-" << land << '\n';
    }
    cout << maxans << '\n';

    return 0;
}

