#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const ll INF = 1e18;
const int maxn = 1e5+5, maxp = 105;

struct Line
{
    ll m, b;
    Line(ll _m, ll _b) : m(_m), b(_b) {}
    ll eval(ll x) {
        return m*x + b;
    }

    friend bool comp(const Line& l1, const Line& l2, const Line& l) {
    	//order in deque: l1, l2, l
    	//true --> l2 is unnecessary
    	ld c1 = (ld)(l2.b-l1.b) * (l2.m-l.m);
    	ld c2 = (l2.b-l.b) * (l2.m-l1.m);
        return c1 >= c2;
    }
};

struct Hull: public deque<Line>
{
    void addBack(const Line& l) {
        while (this->size() >= 2 &&
           comp((*this)[this->size()-2],(*this)[this->size()-1],l)) {
            this->pop_back();    
        }
        this->push_back(l);
    }

    ll query(ll x) { //assumes queries are increasing
        while (this->size() >= 2 &&
               (*this)[0].eval(x) >= (*this)[1].eval(x)) {
            this->pop_front();
        }
        if (this->empty()) return INF;
        return (*this)[0].eval(x);
    }
};

int N, M, P; //N = # of hills, M = number of cats, P = number of feeders
int d[maxn];
ll A[maxn], pfx[maxn];
ll dp[maxp][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> P;
    for (int i = 2; i <= N; i++) {
    	cin >> d[i];
    	d[i] += d[i-1];
    }
    for (int i = 1; i <= M; i++) {
    	int hi, ti; cin >> hi >> ti;
    	A[i] = ti - d[hi];
    }
    sort(A+1,A+M+1);
    for (int i = 1; i <= M; i++) {
        pfx[i] = A[i] + pfx[i-1];    
        dp[1][i] = 1LL*i*A[i] - pfx[i];
    }
    //convex hull DP
    for (int k = 2; k <= P; k++) {
        Hull hull;
        for (int j = 1; j <= M; j++) {
            dp[k][j] = hull.query(A[j]) + j*A[j]-pfx[j]; 
            hull.addBack(Line(-j,dp[k-1][j]+pfx[j]));
        }
    }
    //output
    cout << dp[P][M] << '\n';

    return 0;
}
