#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, k, a[maxn];

struct Node
{
    int cnt;
    Node *child[2];
    Node() {
        cnt = 0;
        child[0] = child[1] = NULL;
    }

    void insert(int x, int i) {
        cnt++;
        if (i >= 0) {
            bool nx = x&(1<<i);
            if (!child[nx]) child[nx] = new Node();
            child[nx]->insert(x,i-1);
        }
        //cout << i << ' ' << x << ": " << cnt << '\n';
    }

    int count(int x, int i) {
        //how many y's in the trie have x^y >= k
        if (i < 0) return cnt;
        int res = 0;
        bool nx = !(x&(1<<i));
        bool K = k&(1<<i);
        if (K) {
            //must take 1 to match k
            if (child[nx]) res += child[nx]->count(x,i-1);
        }
        else {
            //taking 1 is already bigger,
            //taking 0 matches k
            if (child[nx]) res += child[nx]->cnt;
            if (child[!nx]) res += child[!nx]->count(x,i-1);
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i-1];
    }
    Node *root = new Node();
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        root->insert(a[i-1],30);
        ans += root->count(a[i],30);
        //cout << a[i] << ": " << root->count(a[i],30,0) << '\n';
    }
    cout << ans << '\n';
}
