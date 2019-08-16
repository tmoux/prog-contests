#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, r;
multiset<pair<int,int>> ms;
int a[maxn], b[maxn];

vector<pair<int,int>> v;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> r;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        ms.insert({a[i],b[i]});
    }
    int ans = 0;
    while (!ms.empty()) {
        //find all + deltas
        bool found = false;
        pair<int,int> which;
        for (auto it = ms.begin(); it != ms.end(); ++it) {
            if (it->first <= r && it->second >= 0) {
                r += it->second;
                which = *it;
                found = true;
                ans++;
                break;
            }
        }
        if (found) {
            auto it = ms.find(which);
            ms.erase(it);
        }
        if (!found) break;
    }
    //now rating only goes down
    for (auto p: ms) {
        if (p.first > r) {
            continue;
        }
        v.push_back(p);
    }
    while (!v.empty()) {
        sort(v.begin(),v.end(),[](auto a, auto b) {
            if (r+a.second < b.first) return false;
            if (r+b.second < a.first) return true;
            return true;});
        if (r >= v[0].first) {
            r += v[0].second;
            ans++;
            v.erase(v.begin());
            if (r < 0) break;
        }
        else {
            break;
        }
    }
    cout << ans << '\n';
}

