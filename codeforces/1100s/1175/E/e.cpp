#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, maxx = 5e5+5;
int n, m;

int jump[19][maxx];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    deque<pair<int,int>> d;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        d.push_back({l,r});
    }
    sort(d.begin(),d.end(),[](auto a, auto b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second;
            });
    multiset<int> mxr;
    int lp = 0, rp = 0;
    for (int i = 0; i <= 500000; i++) {
        while (rp < n && d[rp].first <= i) {
            //add it
            mxr.insert(d[rp].second);
            rp++;
        }
        if (mxr.empty()) {
            jump[0][i] = -1; //invalid
        }
        else {
            jump[0][i] = *mxr.rbegin(); //get max value
        }
        while (lp < n && d[lp].second <= i) {
            auto it = mxr.find(d[lp].second);
            mxr.erase(it);
            lp++;
        }
        /*
        if (i < 7) {
            cout << i << ": " << jump[0][i] << '\n';
        }
        */
    }
    for (int k = 1; k < 19; k++) {
        for (int i = 0; i <= 500000; i++) {
            if (jump[k-1][i] == -1) jump[k][i] = -1;
            else jump[k][i] = jump[k-1][jump[k-1][i]];
        }
    }
    while (m--) {
        int l, r; cin >> l >> r;
        if (jump[18][l] < r) {
            //can't do it
            cout << -1 << '\n';
        }
        else {
            int ans = 0;
            for (int k = 18; k >= 0; k--) {
                if (jump[k][l] < r) {
                    ans += (1<<k);
                    l = jump[k][l];
                }
            }
            cout << (ans+1) << '\n';
        }
    }
}

