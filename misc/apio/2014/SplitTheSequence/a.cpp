#include <bits/stdc++.h>
using namespace std;
using ll = long long;
typedef long double ld;

const int maxn = 1e5+5, maxk = 205;
int N, K, a[maxn];
ll pre[maxn];
ll dp[2][maxn];
int previous[maxk][maxn];

struct FN
{
    int id;
    ll m, b; //in this case, function is a line
    FN(ll _m, ll _b, int _id) : m(_m), b(_b), id(_id) {}
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
        /*
        if (l1.m == l2.m || l1.m == l.m || l2.m == l.m) {
            printf("(%d, %d), (%d, %d), (%d, %d)\n",l1.m,l1.b,l2.m,l2.b,l.m,l.b);
            fflush(stdout);
            //cout << l1.m << ' ' << l2.m << ' ' << l.m << endl;
        }
        */
    	ld x1 = l1.intersect(l);
        ld x2 = l1.intersect(l2);
        return x1 <= x2;
    }
};

struct Hull: public deque<FN> //convex hull for maximum
{
    void add(const FN& l) {
        //slopes coming in -1,-2,-3,...so add to front of deque rather than back (querying for maximum)
        //if adding to back, need to change the indices
        while (!empty() && back().m == l.m) {
            //assert(back().b <= l.b);
            pop_back();
        }
        while (size() >= 2 && 
            comp(*next(rbegin()),*rbegin(),l)) {
            pop_back();
        }
        /*
        while (!empty() && back().m == l.m) {
            //assert(back().b <= l.b);
            pop_back();
        }
        */
        push_back(l);
        /*
        cout << "----\n";
        for (auto it = begin(); it != end(); ++it) {
            cout << it->m << ' ' << it->b << '\n';
        }
        */
        /*
        if (size() >= 2) {
            assert(next(rbegin())->m != (*rbegin()).m);
        }
        */
    }

    pair<ll,int> query(ll x) {
        while (size() >= 2 && begin()->eval(x) <= next(begin())->eval(x)) {
            pop_front();
        }
        return {begin()->eval(x),begin()->id};
        /*
        pair<ll,int> best = {0,0};
        //cout << "----\n";
        for (auto it = begin(); it != end(); ++it) {
            best = max(best,{it->eval(x),it->id});
            //cout << it->m << ' ' << it->b << '\n';
            if (next(it) != end()) {
                assert(it->m != next(it)->m);
            }
        }
        return best;
        */
    }
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        pre[i] = a[i] + pre[i-1];
    }
    for (int k = 1; k <= K; k++) {
        Hull hull;
        for (int i = 1; i <= N; i++) {
            //if (i-1 == 0 || pre[i-1] > pre[i-2] ||
            //    (pre[i-1] == pre[i-2] && 
            //    dp[i-1][k-1] > dp[i-2][k-1])) {

                hull.add(FN(pre[i-1],dp[1-(k&1)][i-1]-pre[i-1]*pre[i-1],i-1));
            //}
            //else cout << "discounted " << (i-1) << ' ' << (k-1) << '\n';
            auto p = hull.query(pre[i]);
            dp[k&1][i] = p.first;
            previous[k][i] = p.second;
            //printf("[%d][%d]: %d\n",i,k,dp[i][k]);
        }
    }
    /*
    for (int k = 1; k <= K; k++) {
        for (auto p: hulls[k-1]) {
            cout << p.m << ' ' << p.b << '\n';
        }
    }
    */
    //output
    cout << dp[K&1][N] << '\n';
    int curr = N;
    int k = K;
    vector<int> ans;
    while (k > 0) {
        curr = previous[k][curr];
        k--;
        ans.push_back(curr);
    }
    reverse(ans.begin(),ans.end());
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}
