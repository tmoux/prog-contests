#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<int,map<int,vector<vector<int>>>> mp;

vector<int> p;

bool valid(vector<vector<int>>& v) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        set<int> s;
        for (int j = 0; j < n; j++) {
            if (v[i][j] == 0) return false;
            s.insert(v[i][j]);
        }
        if (s.size() != n) return false;
    }
    for (int i = 0; i < n; i++) {
        set<int> s;
        for (int j = 0; j < n; j++) {
            s.insert(v[j][i]);
        }
        if (s.size() != n) return false;
    }
    return true;
}

int trace(vector<vector<int>>& v) {
    int n = v.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += v[i][i];
    }
    return ans;
}

void recurse(int i, vector<vector<int>>& v) {
    if (v.size() == i-1) {
        vector<int> nv(i);
        for (int j = 0; j < i-1; j++) {
            vector<bool> seen(i+1);
            for (int k = 0; k < i-1; k++) {
                seen[v[k][j]] = 1;
            }
            for (int k = 1; k <= i; k++) {
                if (!seen[k]) {
                    nv[j] = k;
                    break;
                }
            }
        }
        v.push_back(nv);
        if (valid(v)) {
            int t = trace(v);
            mp[i][t] = v;
        }
        v.pop_back();
    }
    else {
        vector<int> perm = p;
        do {
            v.push_back(perm);
            recurse(i,v);
            v.pop_back();
        } while (next_permutation(perm.begin(),perm.end()));
    }
}

void solve(int i) {
    p.clear();
    for (int j = 1; j <= i; j++) {
        p.push_back(j);
    }
    vector<vector<int>> v;
    recurse(i,v);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 2; i <= 4; i++) {
        solve(i);
    }
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        int n, k; cin >> n >> k;
        if (mp[n].count(k)) {
            cout << "POSSIBLE\n";
            auto& v = mp[n][k];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << v[i][j] << ' ';
                }
                cout << '\n';
            }
        }
        else {
            cout << "IMPOSSIBLE\n";
        }
    }
}

