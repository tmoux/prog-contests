#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m;
struct Horiz
{
    int x1, x2, y;
};

Horiz horiz[maxn];
int blocks[maxn]; //# blocks in section i - i+1
int pfx[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    if (n == 0) {
        cout << m << '\n';
        return 0;
    }
    vector<int> verts(n);
    for (int i = 0; i < n; i++) {
        cin >> verts[i];    
    }
    sort(verts.begin(),verts.end());
    for (int i = 1; i <= m; i++) {
        cin >> horiz[i].x1 >> horiz[i].x2 >> horiz[i].y;
    }
    for (int i = 1; i <= m; i++) {
        Horiz h = horiz[i];
        int lo;
        if (h.x1 == 1) {
            lo = 0;
        }
        else {
            auto it = lower_bound(verts.begin(),verts.end(),h.x1);
            lo = (int)(distance(verts.begin(),it)) + 1;
        }
        int hi;
        if (h.x1 == 1000000000) {
            hi = n;
        }
        else {
            auto it = upper_bound(verts.begin(),verts.end(),h.x2);
            if (it == verts.begin()) hi = -1;
            else hi = (int)(distance(verts.begin(),it)) - 1;
        }
        //cout << lo << ' ' << hi << '\n';
        if (lo > hi) continue;
        pfx[lo]++;
        pfx[hi+1]--;
    }
    for (int i = 1; i <= n; i++) {
        pfx[i] += pfx[i-1];
    }
    int minans = 999999999;
    for (int i = 0; i <= n; i++) {
        int r = pfx[i] + i;
        minans = min(minans,r);
    }
    cout << minans << '\n';

    return 0;
}

