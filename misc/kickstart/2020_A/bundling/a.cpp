#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, k;

ll ans = 0;

struct Node
{
    Node* nxt[26];
    int cnt;
    int depth;
    Node() {
        cnt = 0;
        for (int i = 0; i < 26; i++) {
            nxt[i] = NULL;
        }
    }
    void insert(const string& s, int i) {
        depth = i;
        if (i == s.size()) {
            cnt++;
            return;
        }
        int nx = s[i]-'A';
        if (!nxt[nx]) nxt[nx] = new Node();
        nxt[nx]->insert(s,i+1);
    }
    int dfs() {
        for (int i = 0; i < 26; i++) {
            if (!nxt[i]) continue;
            cnt += nxt[i]->dfs();
        }
        ans += 1LL*(cnt/k)*depth;
        return cnt%k;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        cin >> n >> k; 
        Node *root = new Node();
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            root->insert(s,0);
        }
        ans = 0;
        root->dfs();
        cout << ans << '\n';
    }
}

