#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef long double ld;
const ll INF = 1e18;

struct FN
{
    ll m, b; //in this case, function is a line
    FN(ll _m, ll _b) : m(_m), b(_b) {}
    ll eval(ll x) const {
        return m*x + b;
    }

    ld intersect(const FN& r) const { //returns x coordinate of intersection
        //assert(m != r.m);
        return (ld)(r.b-b)/(ld)(m-r.m);
    }

    friend bool comp(const FN& l1, const FN& l2, const FN& l) {
    	//order in deque: l1, l2, l
    	//true --> l2 is unnecessary
    	ld x1 = l1.intersect(l);
        ld x2 = l1.intersect(l2);
        return x1 <= x2;
    }
};

struct Hull: public deque<FN> //convex hull for MIN
{
    void addFront(const FN& l) {
        //slopes coming in -3, -2, -1,...so add to front of deque rather than back (querying for maximum)
        //if adding to back, need to change the indices
        while (size() >= 2 && 
            comp(l,(*this)[0],(*this)[1])) {
            pop_front();    
        }
        push_front(l);
    }

    ll query(ll x) { //decreasing order, look from back
        while (size() >= 2 && (*this)[size()-2].eval(x) <= (*this)[size()-1].eval(x)) {
            pop_back();
        }
        if (empty()) return INF;
        return back().eval(x);
    }
};

//iterate over states in decreasing time order
//For each node, keep a separate convex hull
const int maxn = 2e5+5;
int n, m;

map<int,ll> dp[maxn];
Hull hulls[maxn];

struct Event
{
    int time_s, time_e, type, from, to; 
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<Event> states; //{time,{node,start/end}}
    //0 = start, 1 = end
    for (int i = 0; i < m; i++) {
        int a, b, s, e; cin >> a >> b >> s >> e;
        dp[b][e] = INF;
        dp[a][s] = INF;
        states.push_back({s,e,0,a,b});
        states.push_back({s,e,1,a,b});
    }
    sort(states.begin(),states.end(),[](auto a, auto b) {
            int ta = a.type==0?a.time_s:a.time_e;
            int tb = b.type==0?b.time_s:b.time_e;
            return ta > tb;
            });
    states.push_back({0,0,1,1,1});
    //hull[n].addFront(FN(0,0));
    //go through states in decreasing time order
    for (auto p: states) {
        int type = p.type;
        int t = type==0?p.time_s:p.time_e;
        int i = type==0?p.from:p.to;
        //printf("time = %d, node = %d, type = %d\n",t,i,type);
        if (i == n) {
            dp[i][t] = 0;
        }
        else {
            if (type == 0) {
                //start, add to hull
                //printf("equal to dp[%d][%d] = %lld\n",p.to,p.time_e,dp[p.to][p.time_e]);
                dp[i][t] = dp[p.to][p.time_e];
                hulls[i].addFront(FN(-2*t,1LL*t*t+dp[i][t]));
            }
            else {
                dp[i][t] = hulls[i].query(t) + 1LL*t*t;
            }
        }
        //printf("dp[%d][%d] = %lld\n",i,t,dp[i][t]);
    }
    cout << dp[1][0] << '\n';
}

