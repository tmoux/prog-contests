#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

namespace superIO {
	//only for reading ints/lls
	//really only useful when input is greater than 10^6
	//but it is super fast
	int BUF=100000;
	int buf_readed = 0;
	int buf_index = 0;
	char buffer[100000];
	/*****************************************/
	char my_getchar(){
	    char x;
	    if(buf_index==buf_readed){
	        buf_index=0;
	        buf_readed=fread(buffer,1,BUF,stdin);
	    }   
	    x=buffer[buf_index];
	    buf_index++;
	    return x;
	}
	/*************************************/
	ll getInt(){
	    ll r=0LL;
	    char c;
	    int sign=1;
	    while(1){
	        c=my_getchar();
	        if(c=='-')
	            sign=-1;
	 
	        if((c>='0' && c<='9')){
	            r=(c-'0');
	            break;
	        }
	    }
	    while(1){
	        c=my_getchar();
	            if(!(c>='0' && c<='9'))
	                break;
	        r=r*10+(c-'0');
	    }
	    return sign*r;
	}
}
using namespace superIO;

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
    void addFront(const FN& l) {
        //slopes coming in -1,-2,-3,...so add to front of deque rather than back (querying for maximum)
        while (this->size() >= 2 && 
            comp(l,(*this)[0],(*this)[1])) {
            this->pop_front();    
        }
        this->push_front(l);
    }

    ll query(ll x) { //query from back, since queries are decreasing
        while (this->size() > 1 && (*this)[this->size()-1].eval(x) <= (*this)[this->size()-2].eval(x)) {
        	this->pop_back();
        }    
        if (this->empty()) return 0;
        return this->back().eval(x);
    }
};

const int maxn = 1e6+6;
int N;
struct Rec
{	
	ll x, y, a;
} recs[maxn];

ll dp[maxn];



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    N = getInt();
    for (int i = 0; i < N; i++) {
    	recs[i].x = getInt();
    	recs[i].y = getInt();
    	recs[i].a = getInt();
    	//cin >> recs[i].x >> recs[i].y >> recs[i].a;
    }

    sort(recs,recs+N,[](auto& a, auto& b) {
    	if (a.x != b.x) return a.x < b.x;
    	assert(a.y != b.y);
    	return a.y > b.y;
    });
    for (int i = 0; i < N; i++) {
    	dp[i] = recs[i].x*recs[i].y-recs[i].a;
    }
    Hull hull;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
    	ll q = hull.query(recs[i].y) + recs[i].y*recs[i].x-recs[i].a;
    	dp[i] = max(dp[i],q);
    	ans = max(ans,dp[i]);
    	//cout << i << ": " << dp[i] << '\n';
    	hull.addFront(FN(-recs[i].x,dp[i]));
    }
    cout << ans << '\n';

    return 0;
}