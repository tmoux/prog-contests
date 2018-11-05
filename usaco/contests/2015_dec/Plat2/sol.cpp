#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 120000;
struct node
{
    int pts=0, needs=0, extras=0;
    node() {
        pts = 0;
        needs = 0;
        extras = 0;
    }
    node(int i, int j, int k) {
        pts = i;
        needs = j;
        extras = k;
    }

} seg[4*maxn];
int s[4*maxn], e[4*maxn];

int n, elsie[maxn], bessie[maxn];

void build(int i, int l, int r) {
    s[i] = l, e[i] = r;
    if (l == r) return;
    int m = (l+r)>>1;
    build(i*2,l,m);
    build(i*2+1,m+1,r);
}

void insert(int i, int x, bool is) { //is == 0 -> elsie, is == 1 -> bessie
    if (!(s[i] <= x && x <= e[i])) return;
    if (s[i] == e[i]) {
        if (!is) {
            seg[i].needs = 1;        
        }
        else seg[i].extras = 1;
    }
    else {
        insert(i*2,x,is);
        insert(i*2+1,x,is);
        seg[i].pts = seg[i*2].pts + seg[i*2+1].pts;
        seg[i].needs = seg[i*2].needs + seg[i*2+1].needs;
        seg[i].extras = seg[i*2].extras + seg[i*2+1].extras;
        int make = min(seg[i*2].needs,seg[i*2+1].extras);
        seg[i].pts += make;
        seg[i].needs -= make;
        seg[i].extras -= make;
    }
}

vector<int> solve(int A[], int B[]) {
    vector<int> R(n+1,0);
    for (int i = 1; i <= 4*maxn; i++) seg[i] = node(0,0,0);
    for (int i = 1; i <= n; i++) {
        insert(1,A[i],0);
        insert(1,B[i],1);
        R[i] = seg[1].pts;
    }
    return R;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("cardgame.in","r",stdin);
    //freopen("cardgame.out","w",stdout);
    cin >> n;
    build(1,1,2*n);
    vector<bool> seen(2*n+1);
    for (int i = 1; i <= n; i++) {
        cin >> elsie[i];
        seen[elsie[i]] = true;
    }
    int idx = 1;
    for (int i = 2*n; i >= 1; i--) {
        if (!seen[i]) bessie[idx++] = i;
    }
    //done with input
    vector<int> highs = solve(elsie,bessie);
    reverse(elsie+1,elsie+n+1);
    reverse(bessie+1,bessie+n+1);
    for (int i = 1; i <= n; i++) {
        elsie[i] = 2*n+1-elsie[i];
        bessie[i] = 2*n+1-bessie[i];
    }
    vector<int> lows = solve(elsie,bessie); 
    int maxans = 0;
    for (int i = 0; i <= n; i++) {
        int r = highs[i] + lows[n-i];
        maxans = max(maxans,r);
    }
    cout << maxans << '\n';
    
    return 0;
}

