#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1<<19+5;
int n, m, a[maxn];

struct Node
{
    Node *nxt[2];
    int val;
    Node() {
        val = 0;
        nxt[0] = nxt[1] = NULL;
    }
    void insert(int x, int pos) {
        if (pos == -1) {
            val = x;
            return;
        }
        bool i = x & (1<<pos);
        if (!nxt[i]) nxt[i] = new Node();
        nxt[i]->insert(x,pos-1);
    }
    int find_min(int x, int pos) { //element in trie that has min xor w/ x
        if (pos == -1) return val;
        bool i = x & (1<<pos);
        if (nxt[i]) return nxt[i]->find_min(x,pos-1);
        return nxt[!i]->find_min(x,pos-1);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a[ai] = 1;
    }
    Node *root = new Node();
    for (int i = 0; i < (1<<19); i++) {
        if (!a[i]) root->insert(i,18);
    }
    int x = 0;
    while (m--) {
        int ai; cin >> ai;
        x ^= ai;
        cout << (root->find_min(x,18)^x) << '\n';
    }
}

