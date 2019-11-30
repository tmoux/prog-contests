#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, blk = 1005;
int n;
pair<int,int> a[maxn];

vector<pair<pair<int,int>,int>> grid[blk];

int dist(pair<int,int> a, pair<int,int> b) {
    return abs(a.first-b.first) + abs(a.second-b.second);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        int y = a[i].second/1000;
        grid[y].push_back({a[i],i+1});
    }
    vector<int> ans;
    for (int i = 0; i <= 1000; i++) {
        if (i&1) {
            sort(grid[i].begin(),grid[i].end(),[](auto a, auto b) {
                    return a.first.first < b.first.first;
                    });
            for (auto p: grid[i]) {
                ans.push_back(p.second);
            }
        }
        else {
            sort(grid[i].begin(),grid[i].end(),[](auto a, auto b) {
                    return a.first.first > b.first.first;
                    });
            for (auto p: grid[i]) {
                ans.push_back(p.second);
            }
        }
    }
    //output
    ll tot = 0;
    const ll mx = 25000000000;
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
        if (i > 0) {
            tot += dist(a[ans[i]-1],a[ans[i-1]-1]);
        }
    }
    //cerr << tot << endl;
    assert(tot <= mx);
    cout << '\n';
}

