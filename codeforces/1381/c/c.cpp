#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, x, y; cin >> n >> x >> y;
    vector<int> a(n,0);
    map<int,vector<int>> mp;
    set<pair<int,int>> s;
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        int bi; cin >> bi;
        b[i] = bi;
        mp[bi].push_back(i);
    }
    int nomatch = 0;
    for (int i = 1; i <= n+1; i++) {
        if (!mp.count(i)) {
            nomatch = i;
            break;
        }
    }
    assert(nomatch != 0);
    for (auto& p: mp) {
        s.insert({p.second.size(),p.first});
    }
    for (int i = 0; i < x; i++) {
        auto p = *s.rbegin();
        s.erase(prev(s.end()));
        int id = mp[p.second].back(); mp[p.second].pop_back();
        a[id] = p.second;
        s.insert({p.first-1,p.second});
    }

    int m = y-x;
    vector<int> v;
    for (auto p: s) {
        auto& vec = mp[p.second];
        for (auto i: vec) {
            v.push_back(i);
        }
    }
    /*
    cout << "m = " << m << endl;
    for (auto i: v) {
        cout << i << ' ';
    }
    cout << '\n';
    for (auto i: v) {
        cout << b[i] << ' ';
    }
    cout << '\n';
    */
    int idx = v.size()/2;
    for (int i = 0, cnt = 0; i < v.size(); i++) {
        if (cnt < m) {
            if (b[v[i]] != b[v[(i+idx)%v.size()]]) {
                a[v[i]] = b[v[(i+idx)%v.size()]];
                cnt++;
            }
            else a[v[i]] = nomatch;
        }
        else a[v[i]] = nomatch;
    }
    //validate
    int X = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) X++;
    }
    map<int,int> mpA, mpB;
    for (int i = 0; i < n; i++) {
        mpA[a[i]]++;
        mpB[b[i]]++;
    }
    int Y = 0;
    for (auto p: mpA) {
        Y += min(mpA[p.first],mpB[p.first]);
    }
    if (x == X && y == Y) {
    //if (true) {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
        /*
        for (int i = 0; i < n; i++) {
            cout << b[i] << ' ';
        }
        cout << '\n';
        */
    }
    else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
