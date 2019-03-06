#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n, q;
pair<int,int> v[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= q; i++) cin >> v[i].first >> v[i].second;
    sort(v+1,v+q+1,[](auto a, auto b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second;
            });
    vector<pair<int,int>> ps;
    int taken = 0;
    ps.push_back(v[1]);
    for (int i = 2; i <= q; i++) {
        if (v[i].second <= ps.back().second) {
            taken++;
        }
        else {
            ps.push_back(v[i]);
        }
    }
    int total = 0;
    int prev = 1;
    for (auto p: ps) {
        total += p.second - max(p.first,prev) + 1;
        prev = p.second;
        cout << p.first << ' ' << p.second << '\n';
        cout << total << '\n';
    }

    return 0;
}

