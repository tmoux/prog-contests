#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool contains(pair<int,int> a, pair<int,int> b) {
    //returns if a contains b
    return a.first <= b.first && a.second >= b.second;
}

bool intersects(pair<int,int> a, pair<int,int> b) {
    if (a.first > b.first) swap(a,b);
    return a.second >= b.first;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pair<int,int>> sorted, notsorted;
    bool poss = true;
    for (int i = 0; i < m; i++) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 0) {
            notsorted.push_back({l,r});
        }
        else {
            sorted.push_back({l,r});
        }
    }
    sort(sorted.begin(),sorted.end());
    vector<pair<int,int>> invls;
    if (!sorted.empty()) {
        pair<int,int> curr = sorted[0];
        for (int i = 1; i < sorted.size(); i++) {
            if (intersects(curr,sorted[i])) {
                curr.second = max(curr.second,sorted[i].second);
            }
            else {
                invls.push_back(curr);
                curr = sorted[i];
            }
        }
        invls.push_back(curr);
    }
    /*
    for (auto p: invls) {
        cout << p.first << ' ' << p.second << '\n';
    }
    */
    vector<int> ans(n+1);
    for (auto p: notsorted) {
        int l = p.second;
        for (auto q: invls) {
            if (contains(q,p)) {
                poss = false;
                break;
            }
            else {
                if (p.first < q.first && q.first <= p.second) {
                    l = q.first;
                }
            }
        }
        if (!poss) break;
        else {
            ans[l] = -1;
        }
    }
    if (!poss) {
        cout << "NO\n";
    }
    else {
        cout << "YES\n";
        ans[0] = 10000;
        for (int i = 1; i <= n; i++) {
            ans[i] = ans[i-1] + ans[i];
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}

