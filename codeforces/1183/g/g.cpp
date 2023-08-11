#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
int a[maxn], f[maxn]; //type, want it or not

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    while (q--) {
        map<int,int> mp[2];
        cin >> n;
        for (int i = 0; i < n; i++) {
            int ai, fi; cin >> ai >> fi;
            mp[fi][ai]++;
        }
        map<int,pair<int,int>> mp2;
        for (auto p: mp[0]) {
            //cout << p.first << ' ' << p.second << '\n';
            mp2[p.first] = {p.second,p.second};
        }
        for (auto p: mp[1]) {
            //cout << p.first << ' ' << p.second << '\n';
            mp2[p.first].first += p.second;
        }
        map<int,vector<pair<int,int>>> mp3;
        for (auto p: mp2) {
            /*
            cout << p.first << ":\n";
            cout << p.second.first << ' ' << p.second.second << '\n';
            */
            mp3[p.second.first].push_back(p.second);
        }
        /*
        for (auto p: mp3) {
            cout << p.first << ":\n";
            for (auto q: p.second) {
                cout << q.first << ' ' << q.second << '\n';
            }
        }
        */
        auto cmp = [](pair<int,int> a, pair<int,int> b) {
            return (a.first-a.second) > (b.first-b.second);
        };
        multiset<pair<int,int>,decltype(cmp)> s(cmp);
        int ans = 0, mxn = 0;
        for (int i = n; i >= 1; i--) {
            for (auto p: mp3[i]) {
                s.insert(p);
            }
            auto it = s.begin(); 
            if (it != s.end()) {
                int use = min(i,it->first - it->second);
                ans += i;
                mxn += use;
                s.erase(it);
            }
        }
        cout << ans << ' ' << mxn << '\n';
    }
}

