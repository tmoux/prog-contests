#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

template<typename T>
struct FN
{
    T m, b; //in this case, function is a line
    FN(T _m, T _b) : m(_m), b(_b) {}

    ld intersect(const FN& r) const { //returns x coordinate of intersection
        //assert(m != r.m);
        return (ld)(r.b-b)/(ld)(m-r.m);
    }

    friend bool comp(const FN& l1, const FN& l2, const FN& l) {
    	//order in deque: l1, l2, l
    	//true --> l2 is unnecessary
    	ld x1 = l1.intersect(l);
        ld x2 = l1.intersect(l2);
        return x1 < x2;
    }
};

template<typename T>
struct Hull: public deque<FN<T>> //convex hull for minimum
{
    void addBack(const FN<T>& l) {
        if (!this->empty() && this->back().m == l.m && l.b > this->back().b) return; 
        while (this->size() >= 2 && 
            comp((*this)[this->size()-2],(*this)[this->size()-1],l)) {
            this->pop_back();    
        }
        this->push_back(l);
    }
};

const int maxn = 2e5+5;
int n;
map<pair<ld,ld>,vector<int>> cnt;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        ld si = 100000/(ld)a;
        ld ri = 100000/(ld)b;
        cnt[make_pair(si,ri)].push_back(i+1);
    }
    vector<pair<ld,ld>> lines;
    for (auto& p: cnt) lines.push_back(p.first);
    sort(lines.begin(),lines.end(),[](auto& a, auto& b) {
            return a.first > b.first;
            });
    Hull<ld> hull;
    for (auto p: lines) {
        FN<ld> fn(p.first,p.second);
        hull.addBack(fn);
    }
    while (hull.size() >= 2 && hull[0].intersect(hull[1]) <= 0) {
        hull.pop_front();
    }
    vector<int> ans;
    for (FN<ld> fn: hull) {
        for (int i: cnt[make_pair(fn.m,fn.b)]) {
            ans.push_back(i);
        }
    }
    sort(ans.begin(),ans.end());
    //output
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}

