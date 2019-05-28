#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m, a[maxn];

int gleft(multiset<int>& ms, int fi) {
    auto it = ms.upper_bound(0);
    if (it != ms.end()) {
        return m-(*it);
    }
    else return 0;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    bool poss = true;
    for (int i = 1; i < n; i++) {
        if (a[i+1] < a[i]) {
            poss = false;
            break;
        }
    }
    if (poss) {
        cout << 0 << '\n';
        return 0;
    }
    else {
        int fi = a[0];
        multiset<int> left;
        for (int i = 1; i <= n; i++) {
            left.insert(a[i]);
        }
        int ans = gleft(left,fi);
        //cout << "first ans = " << ans << '\n';
        int maxr = 0, minr = maxn + 3;
        int gright = 0;
        for (int i = n; i >= 1; i--) {
            auto it = left.find(a[i]);
            left.erase(it);
            minr = min(minr,a[i]);
            gright = max(gright,a[i]-minr);
            ans = min(ans,max(gleft(left,fi),gright));
            //printf("%d: left = %d, right = %d\n",i,gleft(left,fi),gright);
        }
        cout << ans << '\n';
    }
}

