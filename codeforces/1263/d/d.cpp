#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

bool used[30];

int parent[maxn]; //memset to -1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    int n; cin >> n;
    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        v.push_back(s);
        for (char c: s) {
            used[c-'a'] = true;
        }
        for (int i = 1; i < s.size(); i++) {
            Union(s[i-1]-'a',s[i]-'a');
        }
    }
    int ans = 0;
    for (int i = 0; i < 26; i++) {
        if (used[i] && i == Find(i)) {
            ans++;
        }
    }
    cout << ans << '\n';
}

