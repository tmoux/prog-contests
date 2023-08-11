#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

const int maxn = 305;
int n, m, a[maxn];
pii interval[maxn];

inline bool contains(pii& i, int b) {
    return i.first <= b && b <= i.second;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) {
        cin >> interval[i].first >> interval[i].second;
    }
    pair<int,vector<int>> ans = {0,{}};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int mx = a[i];
            int mn = a[j];
            vector<int> res;
            for (int k = 1; k <= m; k++) {
                pii& p = interval[k];
                if (contains(p,j) && !contains(p,i)) {
                    mn--;
                    res.push_back(k);
                }
            }
            ans = max(ans,{mx-mn,res});
        }
    }
    cout << ans.first << '\n';
    cout << ans.second.size() << '\n';
    for (int i: ans.second) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}

