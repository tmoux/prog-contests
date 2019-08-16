#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N, M;
vector<pair<int,int>> v;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int l, r; cin >> l >> r;
        v.push_back({l,r});
    }
    sort(v.begin(),v.end());
    //sort(v.begin(),v.end(),[](auto a, auto b) {
            //if (a.first != b.first) return a.first < b.first;
            //return a.second > b.second;
            //});
    set<int> pq;
    for (int i = 1; i <= M; i++) {
        pq.insert(i);
    }
    vector<pair<int,int>> rights;
    for (auto p: v) {
        if (pq.empty()) {
            rights.push_back(p);
            continue;
        }
        int mn = *pq.begin();
        if (mn <= p.first) {
            pq.erase(pq.begin());
        }
        else {
            rights.push_back(p);
        }
    }
    sort(rights.begin(),rights.end(),[](auto a, auto b) {
            return a.second > b.second;
            });
    int ans = 0;
    for (auto p: rights) {
        if (pq.empty()) {
            ans++;
            continue;
        }
        int mx = *pq.rbegin();
        if (mx >= p.second) {
            pq.erase(prev(pq.end()));
        }
        else {
            ans++;
        }
    }
    cout << ans << '\n';
}

