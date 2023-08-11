#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
int a[maxn];

struct Node
{
    Node* nxt[2];
    Node() {
        nxt[0] = nxt[1] = NULL;
    }
    void insert(int x, int i) {
        if (i == -1) return;
        bool nx = x & (1<<i);
        if (!nxt[nx]) nxt[nx] = new Node();
        nxt[nx]->insert(x,i-1);
    }

    int f(int i) {
        if (i == -1) return 0;
        if (nxt[0] && !nxt[1]) {
            return nxt[0]->f(i-1);
        }
        if (nxt[1] && !nxt[0]) {
            return nxt[1]->f(i-1);
        }
        return min(nxt[0]->f(i-1),nxt[1]->f(i-1))+(1<<i);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    Node *root = new Node();
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        root->insert(a[i],30);
    }
    int ans = root->f(30);
    cout << ans << '\n';
}

