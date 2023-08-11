#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, k;
vector<int> a[maxn];

inline int compute(int mask, const vector<int>& vec) {
    int r = 0;
    for (int i = 0; i < k; i++) {
        int c = ((1 << i) & mask) ? 1 : -1;
        r += c*vec[i];
    }
    return r;
}

int s[4*maxn], e[4*maxn], mn[1<<5][4*maxn], mx[1<<5][4*maxn];

void pull(int i, int j) {
    mn[j][i] = min(mn[j][i*2],mn[j][i*2+1]);
    mx[j][i] = max(mx[j][i*2],mx[j][i*2+1]);
}
void build(int i, int l, int r) {
    s[i] = l;
    e[i] = r;
    if (l == r) {
        for (int mask = 0; mask < (1<<k); mask++) {
            mn[mask][i] = compute(mask,a[l]);
            mx[mask][i] = mn[mask][i];
        }
        return;
    }
    int m = (l+r)/2;
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    for (int mask = 0; mask < (1<<k); mask++) {
        pull(i,mask);
    }
}
void update(int i, int j, int idx, vector<int>& v) {
    //add x to a[idx];
    if (e[i] < idx || s[i] > idx) return;
    if (s[i] == idx && e[i] == idx) {
        mn[j][i] = compute(j,v);
        mx[j][i] = mn[j][i];
        return;
    }
    update(i*2,j,idx,v);
    update(i*2+1,j,idx,v);
    pull(i,j);
}

int getmin(int i, int j, int l, int r) {
    if (e[i] < l || s[i] > r) return 1e9;
    if (l <= s[i] && e[i] <= r) return mn[j][i];
    return min(getmin(i*2,j,l,r),getmin(i*2+1,j,l,r));
}
int getmax(int i, int j, int l, int r) {
    if (e[i] < l || s[i] > r) return -1e9;
    if (l <= s[i] && e[i] <= r) return mx[j][i];
    return max(getmax(i*2,j,l,r),getmax(i*2+1,j,l,r));
}

int main()
{
    scanf("%d %d",&n,&k);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            int ai; scanf("%d",&ai);
            a[i].push_back(ai);
        }
    }
    build(1,1,n);
    int q; scanf("%d",&q);
    while (q--) {
        int t; scanf("%d",&t);
        if (t == 1) {
            vector<int> nv(k);
            int idx; scanf("%d",&idx);
            for (int i = 0; i < k; i++) {
                scanf("%d",&nv[i]);
            }
            for (int i = 0; i < (1<<k); i++) {
                update(1,i,idx,nv);        
            }
        }
        else {
            int l, r; scanf("%d %d",&l,&r);
            int ans = -1e9;
            for (int i = 0; i < (1<<k); i++) {
                int r1 = getmax(1,i,l,r);
                int r2 = getmin(1,i,l,r);
                ans = max(ans,r1-r2);
            }
            printf("%d\n",ans);
        }
    }
    
    return 0;
}
