#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
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

} seg[9*maxn], seg2[9*maxn];
int s[9*maxn], e[9*maxn];

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
    //printf("Node [%d,%d]: pts=%d, needs=%d, extras=%d\n",s[i],e[i],seg[i].pts,seg[i].needs,seg[i].extras);
}

void insert2(int i, int x, bool is) { //is == 0 -> elsie, is == 1 -> bessie
    if (!(s[i] <= x && x <= e[i])) return;
    if (s[i] == e[i]) {
        if (!is) {
            seg2[i].needs = 1;        
        }
        else seg2[i].extras = 1;
    }
    else {
        insert2(i*2,x,is);
        insert2(i*2+1,x,is);
        seg2[i].pts = seg2[i*2].pts + seg2[i*2+1].pts;
        seg2[i].needs = seg2[i*2].needs + seg2[i*2+1].needs;
        seg2[i].extras = seg2[i*2].extras + seg2[i*2+1].extras;
        int make = min(seg2[i*2].extras,seg2[i*2+1].needs);
        seg2[i].pts += make;
        seg2[i].needs -= make;
        seg2[i].extras -= make;
    }
    //printf("Node [%d,%d]: pts=%d, needs=%d, extras=%d\n",s[i],e[i],seg2[i].pts,seg2[i].needs,seg2[i].extras);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("cardgame.in","r",stdin);
    freopen("cardgame.out","w",stdout);
    cin >> n;
    build(1,1,2*n);
    vector<bool> seen(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> elsie[i];
        seen[elsie[i]] = true;
    }
    int idx = 1;
    for (int i = 2*n; i >= 1; i--) {
        if (!seen[i]) bessie[idx++] = i;
    }
    //done with input
    vector<int> highs(n+1,0);
    for (int i = 1; i <= n; i++) {
        insert(1,elsie[i],0);
        insert(1,bessie[i],1);
        highs[i] = seg[1].pts;
        //cout << i << ": " << highs[i] << '\n';
    }
    //do lows
    vector<int> lows(n+2,0);
    for (int i = n; i >= 1; i--) {
        insert2(1,elsie[i],0);
        insert2(1,bessie[i],1);
        lows[i] = seg2[1].pts;
        //cout << i << ": " << lows[i] << '\n';
    }
    int maxans = 0;
    for (int i = 0; i <= n; i++) {
        int r = highs[i] + lows[i+1];
        maxans = max(maxans,r);
    }
    cout << maxans << '\n';
    

    return 0;
}

