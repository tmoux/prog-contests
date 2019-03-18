#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using int128 = __int128;

const int maxn = 3005;
int N;

ll ch3(ll x) {return x*(x-1)*(x-2)/6;}
ll ch2(ll x) {return x*(x-1)/2;}

void reduce(int128

struct Line
{
    ld m, b;
    Line(ll x1, ll y1, ll x2, ll y2) {
        ll num = y2-y1;
        ll den = x2-x1;
        if (den == 0) {
            m = inf;                    
            b = x1;
        }
        else {
            m = (ld)num/den;
            b = (ld)y1 - m*x1;
        }
    }

    bool operator<(const Line& r) const {
        if (abs(m-r.m) > eps) return m < r.m;
        if (abs(b-r.b) > eps) return b < r.b;
        return false;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    vector<pair<ll,ll>> pts;
    for (int i = 0; i < N; i++) {
        ll x, y; cin >> x >> y;
        pts.push_back({x,y});
    }
    map<Line,int> cnt;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            Line l = Line(pts[i].first,pts[i].second,pts[j].first,pts[j].second);
            ++cnt[l];
        }
    }
    ll total = ch3(N);
    map<ll,int> remap; //maps (n choose 2) --> n
    for (int i = 1; i <= N; i++) {
        remap[ch2(i)] = i;
    }
    for (auto p: cnt) {
        int c = p.second;
        ll takeout = ch3(remap[c]);
        total -= takeout;
    }
    cout << total << '\n';
}

