#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;
ll s[maxn];
ll ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s,s+n);
    vector<pair<ll,int>> spaces; //-1 = not query,
    //i = query
    for (int i = 0; i < n - 1; i++) {
        spaces.push_back({s[i+1]-s[i],-1});
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        ll l, r; cin >> l >> r;
        spaces.push_back({r-l,i});
    }
    sort(spaces.begin(),spaces.end());

}

