#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<bool,int> check(int n, map<int,vector<int>> mp) {
    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int aa = 1; aa <= t; aa++) {
        cout << "Case #" << aa << ": ";
        int N, C, M;
        cin >> N >> C >> M;
        map<int,vector<int>> mp; //maps id to tickets
        for (int i = 0; i < m; i++) {
            int p, b; cin >> p >> b;
            mp[b].push_back(p);
        }
        int lo = 0, hi = M+1;
        int numPromote = 0;
        while (lo + 1 < hi) {
            int mid = (lo+hi)/2;
            auto c = check(mid,mp);
            if (c.first) {
                numPromote = c.second;
                hi = mid;
            }
            else lo = mid;
        }

        cout << hi << ' ' << numPromote << '\n';
    }
}

