#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n;

int pt = 0;
int trie[maxn][26];

int insert(int i, int c) {
    if (trie[i][c] != -1) return trie[i][c];
    return trie[i][c] = ++pt;
}

bool is[maxn];
int ord[maxn], ans[maxn];

struct ST
{
    vector<int> v = {maxn};
    int aux = 0;
    void add(int x) {
        v.push_back(min(v.back(),x-aux));
    }
    int query_min() {
        return v.back()+aux;
    }
    void add_all() {
        ++aux;
    }
    void pop() {
        v.pop_back();
    }
};
ST st;
int dp[maxn];

void dfs(int i, int p) {
    if (i > 0) {
        dp[i] = dp[p] + 1;
        if (is[i]) {
            dp[i] = min(dp[i],st.query_min());
            ans[ord[i]] = dp[i];
        }
    }
    st.add(dp[i]+1);
    if (is[i]) st.add_all();
    for (int j = 0; j < 26; j++) {
        if (trie[i][j] == -1) continue;
        dfs(trie[i][j],i);
    }
    st.pop();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(trie,-1,sizeof trie);
    cin >> n;
    vector<int> v; v.push_back(0);
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        char c; cin >> c;
        v.push_back(insert(v[p],c-'a'));
    }
    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        int ai; cin >> ai;
        is[v[ai]] = true;
        ord[v[ai]] = i;
    }
    dfs(0,0);
    for (int i = 0; i < k; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

