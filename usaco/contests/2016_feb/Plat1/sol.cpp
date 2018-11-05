#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+100;
const int INF = 1e9;
int n;

struct Seg //segtree for sum
{
    int *s, *e;
    int *node;
    Seg() {
        s = new int[4*maxn];
        e = new int[4*maxn];
        node = new int[4*maxn];
    }
    void build(int i, int l, int r) {
        s[i] = l, e[i] = r;
        if (l == r) {
            node[i] = 0;
            return;
        }
        int m = (l+r)>>1;
        build(i*2,l,m);
        build(i*2+1,m+1,r);
        node[i] = 0;
    }
    void add(int i, int j, int x) {
        if (!(s[i] <= j && j <= e[i])) return;
        if (s[i] == e[i]) {
            node[i] += x;
            return;
        }
        add(i*2,j,x);
        add(i*2+1,j,x);
        node[i] = node[i*2] + node[i*2+1];
    }
    int sum(int i, int l, int r) {
        if (r < s[i] || l > e[i]) return 0;
        if (l <= s[i] && e[i] <= r) return node[i];
        return sum(i*2,l,r) + sum(i*2+1,l,r);
    }
};

struct Point
{
    int x, y, y_compress; 
};

pair<pair<int,int>,pair<int,int>> calc(int m, Seg& lside, Seg& rside) { 
    if (m > n || m < 1) return {{INF,INF},{INF,INF}};
    return {{lside.sum(1,0,m),rside.sum(1,0,m)},{lside.sum(1,m+1,n+4),rside.sum(1,m+1,n+4)}};
}

inline int mx(pair<pair<int,int>,pair<int,int>> p) {
    return max(max(p.first.first,p.first.second),max(p.second.first,p.second.second));
}

inline int eval(pair<pair<int,int>,pair<int,int>> p) {
    return max(p.first.first+p.first.second,p.second.first+p.second.second);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifndef OFFLINE
    //freopen("balancing.in","r",stdin); freopen("balancing.out","w",stdout);
    #endif
    cin >> n;
    vector<Point> pts;
    vector<int> ys;
    map<int,int> compress;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        Point p = {x,y};
        pts.push_back(p);
        ys.push_back(y);
    }
    //coordinate compress
    sort(ys.begin(),ys.end());
    int idx = 1;
    for (int i: ys) {
        if (!compress.count(i)) {
            compress[i] = idx;
            idx++;
        }
    }
    for (Point& p: pts) {
        p.y_compress = compress[p.y];
    }
    Seg lside, rside;
    lside.build(1,0,n+10);
    rside.build(1,0,n+10);
    sort(pts.begin(),pts.end(),[](const Point& a, const Point& b) {return a.x < b.x;});    
    for (int i = 0; i < n; i++) {
        rside.add(1,pts[i].y_compress,1);
    }
    vector<int> adds;
    int ans = INF;
    for (int i = 0; i < n; i++) {
        adds.push_back(pts[i].y_compress);
        if (i == n - 1 || pts[i].x != pts[i+1].x) {
            //remove from right, add to left
            for (int j: adds) {
                lside.add(1,j,1);
                rside.add(1,j,-1);
            }
            //ternary search
            int lo = 0, hi = n+1;
            while (lo + 1 < hi) {
                int m = (lo+hi)/2;
                int c1 = eval(calc(m-1,lside,rside));
                int c2 = eval(calc(m,lside,rside));
                int c3 = eval(calc(m+1,lside,rside));
                if (c1 >= c2 && c2 <= c3) {
                    //local minimum found
                    lo = c2;
                    break;
                }
                else if (c1 >= c2 && c2 >= c3) {
                    lo = m;
                }
                else {
                    assert(c1 <= c2 && c2 <= c3);
                    hi = m;
                }
            }
            for (int l = lo-5; l <= lo+5; l++) {
                int r = mx(calc(l,lside,rside));
                ans = min(ans,r);    
            }
            adds.clear();
            
            for (int l = 1; l <= n; l++) {
                //cout << l << ": " << mx(calc(l,lside,rside)) << '\n';
                ans = min(ans,mx(calc(l,lside,rside)));
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
