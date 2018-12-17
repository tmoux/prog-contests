#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxx = 10*maxn;
int N, a[maxn], b[maxn], pos[maxn];
struct Point {
    int x, y;
    bool operator<(const Point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y > rhs.y;
    }
};

Point pts[maxx];
int idx = 0;

struct Seg {
    int *s, *e, *mx;
    Seg(int l, int r) {
        int n = r-l+1;
        s = new int[4*n];
        e = new int[4*n];
        mx = new int[4*n];
        build(1,l,r);
    }
    void build(int i, int l, int r) {
        s[i] = l;
        e[i] = r;
        if (l == r) {
            mx[i] = 0;
            return;
        }
        int m = (l+r)/2;
        build(i*2,l,m);
        build(i*2+1,m+1,r);
        mx[i] = max(mx[i*2],mx[i*2+1]);                    
    }
    void update(int i, int idx, int x) {
        if (s[i] > idx || e[i] < idx) return;
        if (s[i] == idx && e[i] == idx) {
            mx[i] = max(mx[i],x);
            return;
        }
        update(i*2,idx,x);
        update(i*2+1,idx,x);
        mx[i] = max(mx[i*2],mx[i*2+1]);
    }

    int query(int i, int l, int r) {
        if (r < l) return 0;
        if (e[i] < l || s[i] > r) return 0;
        if (l <= s[i] && e[i] <= r) return mx[i];
        return max(query(i*2,l,r),query(i*2+1,l,r));
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("nocross.in","r",stdin); freopen("nocross.out","w",stdout);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> b[i];
        pos[b[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        for (int j = a[i] - 4; j <= a[i] + 4; j++) {
            if (j < 1 || j > N) continue;
            pts[idx++] = {i,pos[j]};
            //cout << a[i] << ' ' << b[pos[j]] << '\n';
            //assert(abs(a[i]-b[pos[j]]) <= 4);
        }
    }
    sort(pts,pts+idx);
    Seg seg(0,idx-1);
    int ans = 0;
    for (int i = 0; i < idx; i++) {
        Point p = pts[i];
        int q = seg.query(1,0,p.y-1);
        seg.update(1,p.y,q+1);
        ans = max(ans,q+1);
        //cout << p.x << ' ' << p.y << ": " << q+1 << '\n';
    }
    cout << ans << '\n';

    return 0;
}

