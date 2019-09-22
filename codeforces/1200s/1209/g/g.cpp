#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, q;
int a[maxn];
int se[maxn], en[maxn];

vector<int> indices[maxn];

int solve(vector<pair<pair<int,int>,int>> v) {
    if (v.empty()) return 0;
    /*
    for (auto p: v) {
        cout << p.first.first << ' ' << p.first.second << ' ' << p.second << '\n';
    }
    cout << '\n';
    */
    int l = n+1, r = -1;
    int maxNum = 0;
    for (auto p: v) {
        int idx = p.second;
        l = min(l,p.first.first);
        r = max(r,p.first.second);
        /*
        auto lo = lower_bound(indices[idx].begin(),indices[idx].end(),p.first.first);
        auto hi = upper_bound(indices[idx].begin(),indices[idx].end(),p.first.second);
        int d = distance(lo,hi);
        */
        int d = indices[idx].size();
        maxNum = max(maxNum,d);
        //cout << idx << ": " << d << '\n';
    }
    //cout << (r-l+1) << ' ' << maxNum << '\n';
    return (r-l+1)-maxNum;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        indices[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (se[a[i]] == 0) se[a[i]] = i;
    }
    for (int i = n; i >= 1; i--) {
        if (en[a[i]] == 0) en[a[i]] = i;
    }
    vector<pair<pair<int,int>,int>> invl;
    for (int i = 1; i <= 200000; i++) {
        if (se[i] != 0) {
            invl.push_back({{se[i],en[i]},i});
        }
    }
    int maxSeen = 0;
    int ans = 0;
    vector<pair<pair<int,int>,int>> curr;
    sort(invl.begin(),invl.end());
    for (auto p: invl) {
        if (p.first.first > maxSeen) {
            ans += solve(curr);
            curr.clear();
            curr.push_back(p);
            maxSeen = max(maxSeen,p.first.second);
        }
        else {
            curr.push_back(p);
            maxSeen = max(maxSeen,p.first.second);
        }
    }
    ans += solve(curr);
    cout << ans << '\n';
}

