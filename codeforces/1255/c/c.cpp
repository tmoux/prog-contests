#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
vector<int> a[maxn];
int deg[maxn];

map<pair<int,int>,int> mp;

vector<int> ord;

void dfs(int i, int p) {
    ord.push_back(i);
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
}

int other(const vector<int>& a, vector<int> b) {
    int p1 = a[a.size()-1];
    int p2 = a[a.size()-2];
    int cnt = 0;
    int res = -1;
    for (int j: b) {
        if (j == p1 || j == p2) cnt++;
        else res = j;
    }
    if (cnt != 2) {
        return -1;
    }
    else return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-2; i++) {
        for (int j = 0; j < 3; j++) {
            int ai; cin >> ai;
            a[i].push_back(ai);
        }
        sort(a[i].begin(),a[i].end());
        auto it = mp.find(make_pair(a[i][0],a[i][1]));
        if (it != mp.end()) {
            int j = it->second;
            deg[i]++;
            deg[j]++;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        else mp[make_pair(a[i][0],a[i][1])] = i;
        
        it = mp.find(make_pair(a[i][1],a[i][2]));
        if (it != mp.end()) {
            int j = it->second;
            deg[i]++;
            deg[j]++;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        else mp[make_pair(a[i][1],a[i][2])] = i;

        it = mp.find(make_pair(a[i][0],a[i][2]));
        if (it != mp.end()) {
            int j = it->second;
            deg[i]++;
            deg[j]++;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        else mp[make_pair(a[i][0],a[i][2])] = i;
    }

    /*
    for (int i = 0; i < n-2; i++) {
        cout << i << ": ";
        for (int j: adj[i]) {
            cout << j << ' ';
        }
        cout << '\n';
    }
    */

    int start = -1;
    for (int i = 0; i < n-2; i++) {
        if (deg[i] == 1) {
            start = i;
            break;
        }
    }
    assert(start != -1);
    dfs(start,start);
    /*
    cout << "ord: " << '\n';
    for (int i: ord) {
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
    */
    do {
        vector<int> ans = {a[ord[0]][0],a[ord[0]][1],a[ord[0]][2]};
        /*
        for (int i = 0; i < 3; i++) {
            cout << a[ord[0]][i] << ' ';
        }
        cout << '\n';
        */
        for (int i = 1; i < ord.size(); i++) {
            //cout << other(ans,a[ord[i]]) << '\n';
            int add = other(ans,a[ord[i]]);
            if (add != -1) {
                ans.push_back(add);
            }
        }
        if (ans.size() == n) {
            for (int i: ans) {
                cout << i << ' ';
            }
            cout << '\n';
            return 0;
        }
    } while (next_permutation(a[ord[0]].begin(),a[ord[0]].end()));
    /*
    
    */
}

