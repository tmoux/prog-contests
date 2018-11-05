#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+100;
const ll INF = 1e18;
int n, m;

struct Seg //segtree for minimum
{
    int *s, *e;
    ll *node;
    Seg() {
        s = new int[4*maxn];
        e = new int[4*maxn];
        node = new ll[4*maxn];
    }
    void build(int i, int l, int r) {
        s[i] = l, e[i] = r;
        if (l == r) {
            node[i] = INF;
            return;
        }
        int m = (l+r)>>1;
        build(i*2,l,m);
        build(i*2+1,m+1,r);
        node[i] = INF;
    }
    void set(int i, int j, ll x) {
        if (!(s[i] <= j && j <= e[i])) return;
        if (s[i] == e[i]) {
            node[i] = min(x,node[i]);
            return;
        }
        set(i*2,j,x);
        set(i*2+1,j,x);
        node[i] = min(node[i*2],node[i*2+1]);
    }
    ll mini(int i, int l, int r) {
        if (r < s[i] || l > e[i]) return INF;
        if (l <= s[i] && e[i] <= r) return node[i];
        return min(mini(i*2,l,r),mini(i*2+1,l,r));
    }
};

struct Point
{
    int x, y, t, id, y_compress; 
};

ll ans[maxn];
inline void amin(ll& a, ll b, ll c) {
    a = min(a,min(b,c));
}

void sweep(vector<Point>& pts, int mult) {
    Seg yup, ydown;
    yup.build(1,1,2e5+5);
    ydown.build(1,1,2e5+5);
    for (Point& p: pts) {
        int comp = p.y_compress;                
        ll x = p.x, y = p.y, t = p.t;
        if (p.t >= 0) { //is slingshot
            yup.set(1,comp,t-mult*x+y);
            ydown.set(1,comp,t-mult*x-y);
        }
        else { //is query point
            int a = p.x;
            int b = p.y;
            ll t1 = yup.mini(1,comp,2e5+5) + mult*a - b;
            ll t2 = ydown.mini(1,1,comp) + mult*a + b;
            amin(ans[p.id],t1,t2);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("slingshot.in","r",stdin); freopen("slingshot.out","w",stdout);
    cin >> n >> m;
    vector<Point> pts;
    vector<int> ys;
    map<int,int> compress;
    for (int i = 0; i < n; i++) {
        int x, y, t; cin >> x >> y >> t;
        Point p = {x,y,t,-1};
        pts.push_back(p);
        ys.push_back(y);
    }
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        Point p = {x,y,-1,i};
        pts.push_back(p);
        ys.push_back(y);
        ans[i] = abs(x-y);
    }
    //coordinate compress
    sort(ys.begin(),ys.end());
    int idx = 1;
    for (int i: ys) {
        if (!compress.count(i)) {
            compress[i] = idx++;
        }
    }
    for (Point& p: pts) {
        p.y_compress = compress[p.y];
    }
    //segtree sweep, first left-to-right
    sort(pts.begin(),pts.end(),[](const Point& a, const Point& b) {if (a.x != b.x) return a.x < b.x; return a.t > b.t;});
    sweep(pts,1); //1 -> left-right, -1 -> right-left
    sort(pts.begin(),pts.end(),[](const Point& a, const Point& b) {if (a.x != b.x) return a.x > b.x; return a.t > b.t;});
    sweep(pts,-1);
    //output
    for (int i = 0; i < m; i++) 
        cout << ans[i] << '\n';
    return 0;
}

