#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef long double ld;

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

struct Hull: public deque<FN> //convex hull for maximum
{
    void addFN(const FN& l) {
        while (this->size() >= 2 && 
            comp((*this)[size()-2],(*this)[size()-1],l)) {
            this->pop_back();    
        }
        this->push_back(l);
    }

    ll query(ll x) {
        if (size() == 0) return -(1LL<<62);
        while (size() >= 2 && (*this)[1].eval(x) >= (*this)[0].eval(x)) {
            pop_front();
        }
        return (*this)[0].eval(x);
    }
};

const int maxn = 3e5+5;
int n, sq;

bool isq[maxn];
ll ans[maxn];

bool in(pair<int,int> a, int b) {
    return a.first <= b && b <= a.second;
}

pair<int,int> t[maxn];
pair<int,int> rec[maxn];
vector<int> adds;

vector<pair<int,int>> queries[maxn];
vector<int> special[maxn];

int main() {
    cin >> n;
    sq = 10*(int)sqrt(n);
    for (int i = 1; i <= n; i++) {
        int tt, a, b; cin >> tt >> a;
        if (tt == 1) {
            cin >> b;
            rec[i] = {a,b};
            adds.push_back(i);
            t[i] = {i,n+1};
        }
        else if (tt == 2) {
            t[a].second = i;
        }
        else {
            queries[(i-1)/sq].push_back({a,i});
            isq[i] = true;
        }
    }
    for (int i: adds) {
        int b = (i-1)/sq;
        special[b].push_back(i);
        if (t[i].second <= n) {
            special[(t[i].second-1)/sq].push_back(i);
        }
    }
    for (int i = 0; i <= (n-1)/sq; i++) {
        if (queries[i].empty()) continue;
        Hull hull;
        vector<pair<int,int>> v;
        for (int j: adds) {
            if (t[j].first >= sq*i+1) break;
            if (t[j].first < sq*i+1 && min(n,sq*(i+1)) < t[j].second) {
                v.push_back(rec[j]);
            }
        }
        sort(v.begin(),v.end());
        for (int j = 0; j < v.size(); j++) {
            if (j == v.size()-1 || v[j].first < v[j+1].first) {
                hull.addFN(FN(v[j].first,v[j].second));
            }
        }
        sort(queries[i].begin(),queries[i].end());
        for (auto p: queries[i]) {
            int id = p.second;
            int q = p.first;
            ans[id] = hull.query(q);
            for (int j: special[i]) {
                if (in(t[j],id)) {
                    ans[id] = max(ans[id],FN(rec[j].first,rec[j].second).eval(q));
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (isq[i]) {
            if (ans[i] > -(1LL<<61)) {
                cout << ans[i] << '\n';
            }
            else {
                cout << "EMPTY SET\n";
            }
        }
    }
}
