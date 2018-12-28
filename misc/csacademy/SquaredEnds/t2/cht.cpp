#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll INF = 1LL<<62;
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

	//can return int or long long
	int getInt(){
	    int r=0LL;
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
    bool is_query;
    FN(ll _m, ll _b, bool is = false) : m(_m), b(_b), is_query(is) {}
    mutable function<ld()> xRight; //right intersection point of line in hull, is infinity for rightmost line
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

    bool operator<(const FN& rhs) const {
        if (!rhs.is_query) return m > rhs.m;
        ll x = rhs.m;
        return xRight() < (ld)x;
    }
};

//goal: dynamic variant of convex hull
//insert, delete, and query in O(log n)
struct Hull: public set<FN> //convex hull for minimum
{
    void addFN(FN fn) {
        Hull::iterator it = lower_bound(fn);
        if (it != end() && it->m == fn.m) {
            if (it->b <= fn.b) return; //no need to consider it
            erase(it);
        }
        it = insert(fn).first;
        //check if it is necessary
        if (it != begin() && next(it) != end()) {
        	if (comp(*prev(it),*it,*next(it))) {
        		//not needed
        		erase(it);
        		return;
        	}
        }
        it->xRight = [=] { return next(it) == end() ? INF : it->intersect(*next(it)); };
        //function pointer magic
        //Removes unnecessary functions above and below
        Hull::iterator b1, b2, f1, f2;
        while (true) {
            if (it == begin()) break;
            else {
                b1 = prev(it);
                if (b1 == begin()) break;
                else {
                    b2 = prev(b1);
                    if (comp(*b2,*b1,*it)) {
                        erase(b1);
                    }  
                    else break;     
                }
            }
        }
        while (true) {
        	if (it == end()) break;
            f1 = next(it);
            if (f1 == end()) break;
            else {
                f2 = next(f1);
                if (f2 == end()) break;
                else {
                    if (comp(*it,*f1,*f2)) {
                        erase(f1);
                    }
                    else break;
                }
            }
        }
    }

    ll query(ll x) {
    	if (this->empty()) return INF;
        auto it = lower_bound(FN(x,0,true));
        return it->eval(x);
        
    }
};

const int maxn = 1e4+4, maxk = 105;
int N, K;
ll A[maxn];
ll dp[maxk][maxn];
inline ll sqr(ll x) { return x*x; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    N = getInt();
    K = getInt();
    for (int i = 1; i <= N; i++) {
    	A[i] = getInt();
    	dp[1][i] = sqr(A[i]-A[1]);
    }
    for (int k = 2; k <= K; k++) {
    	Hull hull;
    	for (int i = 1; i <= N; i++) {
    		
    		dp[k][i] = hull.query(A[i]) + sqr(A[i]);
    		FN fn = FN(-2*A[i+1],dp[k-1][i]+sqr(A[i+1]));
    		hull.addFN(fn);	
    	}
    }
    cout << dp[K][N] << '\n';

    return 0;
}