#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;
ll len[maxn];
char type[maxn];

bool poss(int m) {
    ll stamina = 0;
    for (int i = 0; i <= m; i++) {
        if (type[i] ==     
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> len[i];
    for (int i = 1; i <= n; i++) cin >> type[i];
    int lo = 0, hi = n+1; //hi will be the segment, where it's possible, after charging for the entire segment
    while (lo + 1 < hi) {
        int m = (lo+hi)/2;
        if (poss(m)) hi = m;
        else lo = m;
    }

    return 0;
}

