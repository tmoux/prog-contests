#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, m;

pair<int,int> intersect(pair<int,int> a, pair<int,int> b) {
    return {max(a.first,b.first),min(a.second,b.second)};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        cin >> n >> m;
        map<int,vector<pair<int,int>>> mp;
        for (int i = 0; i < n; i++) {
            int t, l, h; cin >> t >> l >> h;
            mp[t].push_back({l,h});
        }
        vector<pair<int,pair<int,int>>> v;
        bool done = false;
        for (auto p: mp) {
            auto& vec = p.second;
            pair<int,int> cur = vec[0];
            for (int i = 1; i < vec.size(); i++) {
                cur = intersect(cur,vec[i]);
            }
            if (cur.first > cur.second) {
                cout << "NO\n";
                done = true;
                break;
            }
            else {
                v.push_back({p.first,cur});
            }
        }
        if (done) continue;
        int cur = m;
        int exLeft = 0, exRight = 0;
        int prev = 0;
        for (auto p: v) {
            int t = p.first;
            pair<int,int> range = p.second;
            exLeft += t-prev;
            exRight += t-prev;
            if (cur < range.first) {
                if (exRight < range.first-cur) {
                    done = true;
                    break;
                }
                else {
                    exRight -= (range.first-cur);
                    cur = range.first;
                    exRight = min(exRight,range.second-range.first);
                    exLeft = 0;
                }
            }
            else if (cur > range.second) {
                if (exLeft < cur-range.second) {
                    done = true;
                    break;
                }
                else {
                    exLeft -= (cur-range.second);
                    cur = range.second;
                    exLeft = min(exLeft,range.second-range.first);
                    exRight = 0;
                }
            }
            else {
                exRight = min(exRight,range.second-cur);
                exLeft = min(exLeft,cur-range.first);
            }

            prev = t;
        }
        cout << (done ? "NO" : "YES") << endl;
    }
}

