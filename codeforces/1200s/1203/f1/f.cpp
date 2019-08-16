#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, r;
multiset<pair<int,int>> ms;
int a[maxn], b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> r;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        ms.insert({a[i],b[i]});
    }
    while (!ms.empty()) {
        //find all + deltas
        bool found = false;
        for (auto it = ms.begin(); it != ms.end(); ++it) {
            if (it->first <= r && it->second >= 0) {
                r += it->second;
                ms.erase(it);
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    //now rating only goes down
    vector<pair<int,int>> v;
    for (auto p: ms) {
        if (p.first > r) {
            //impossible
            cout << "NO\n";
            return 0;
        }
        v.push_back(p);
    }
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return (a.first+a.second) > (b.first+b.second);
            });
    for (auto p: v) {
        if (p.first > r) {
            cout << "NO\n";
            return 0;
        }
        else {
            r += p.second;
        }
    }
    cout << "YES\n";
}

