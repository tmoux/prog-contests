#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const int maxk = 40;
int n;
ll a[maxn], pre[maxn];

ll total = 0;

struct Node
{
    Node* to[2];
    Node() {
        to[0] = to[1] = NULL;
    }
};

void add(Node *curr, ll x) {
    for (int i = maxk; i >= 0; i--) {
        bool nxt = x&(1LL<<i);
        if (!curr->to[nxt]) curr->to[nxt] = new Node();
        curr = curr->to[nxt];
    }
}

ll getmax(Node *curr, ll x) {
    ll res = 0;
    for (int i = maxk; i >= 0; i--) {
        bool nxt = !(x&(1LL<<i));
        if (curr->to[nxt]) {
            assert(curr->to[nxt]);
            res |= 1ll<<i;
            curr = curr->to[nxt];
        }
        else {
            assert(curr->to[!nxt]);
            curr = curr->to[!nxt];
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total ^= a[i];
    }
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i-1] ^ a[i];
    }
    Node *root = new Node();
    add(root,0);
    ll ans = total;
    for (int i = 1; i <= n; i++) {
        ll r = getmax(root,pre[i]^total);
        //cout << "looking for max with " << (pre[i]^total) << '\n';
        //cout << i << ": " << r << '\n';
        ans = max(ans,r);
        add(root,pre[i]);    
        //cout << "inserting " << pre[i] << '\n';
    }
    cout << ans << '\n';
}

