#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
pair<int,int> ans[maxn];
vector<pair<int,int>> tree;
vector<pair<int,int>> ntree; //weight, id
bool poss = true;

int a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if (b == 1) {
            tree.push_back({a,i});
        }
        else {
            ntree.push_back({a,i});
        }
    }
    sort(tree.begin(),tree.end());
    sort(ntree.begin(),ntree.end(),greater<pair<int,int>>());
    for (int i = 0; i < tree.size(); i++) {
        ans[tree[i].second] = {i+1,i+2};
        a[i+1] = tree[i].first;
    }
    for (int r = 3; r <= n; r++) {
        int mx = a[r-1];
        for (int l = 1; l <= r-2; l++) {
            if (ntree.empty()) break;
            auto p = ntree.back();
            ntree.pop_back();
            if (p.first < mx) {
                poss = false;
                break;
            }
            ans[p.second] = {l,r};
        }
    }
    
    if (poss) {
        for (int i = 0; i < m; i++) {
            cout << ans[i].first << ' ' << ans[i].second << '\n';
        }
    }
    else {
        cout << "-1\n";
    }
}

