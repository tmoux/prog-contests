#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, m;
char ss[maxn];

struct Node
{
    int ans, uLeft, uRight;    
} nodes[4*maxn];

Node comb(Node a, Node b) {
    int t = min(a.uLeft,b.uRight);
    Node ret;
    ret.ans = a.ans + b.ans + 2*t;
    ret.uLeft = a.uLeft + b.uLeft - t;
    ret.uRight = a.uRight + b.uRight - t;
    return ret;
}

int s[4*maxn], e[4*maxn];
void build(int i, int se, int en) {
    s[i] = se;
    e[i] = en;
    if (se == en) {
        if (ss[se] == '(') nodes[i] = {0,1,0};
        if (ss[se] == ')') nodes[i] = {0,0,1};
        return;
    }
    int m = (se+en)>>1;
    build(i*2,se,m);
    build(i*2+1,m+1,en);
    nodes[i] = comb(nodes[i*2],nodes[i*2+1]);
    //printf("[%d,%d]: ans = %d, uLeft = %d, uRight = %d\n",se,en,nodes[i].ans,nodes[i].uLeft,nodes[i].uRight);
}

Node query(int i, int l, int r) {
    if (s[i] == e[i]) return nodes[i];
    if (l <= s[i] && e[i] <= r) return nodes[i];
    int m = (s[i]+e[i])>>1;
    Node ret = {0,0,0};
    if (l <= m) ret = comb(query(i*2,l,r),ret);
    if (r > m) ret = comb(ret,query(i*2+1,l,r));
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string st; cin >> st;
    n = st.size();
    for (int i = 1; i <= n; i++) ss[i] = st[i-1];
    build(1,1,n);
    cin >> m;
    while (m--) {
        int l, r; cin >> l >> r;
        cout << query(1,l,r).ans << '\n';
    }
    return 0;
}
