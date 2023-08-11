#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const ll INF = 1LL<<62;
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
        if (!rhs.is_query) return m < rhs.m;
        ll x = rhs.m;
        return xRight() < (ld)x;
    }
};

//goal: dynamic variant of convex hull
//insert, delete, and query in O(log n)
struct Hull: public set<FN> //convex hull for maximum
{
    void addFN(FN fn) {
        Hull::iterator it = lower_bound(fn);
        if (it != end() && it->m == fn.m) {
            if (it->b >= fn.b) return; //no need to consider it
            erase(it);
        }
        it = insert(fn).first;
        it->xRight = [=] { return next(it) == end() ? INF : it->intersect(*next(it)); };
        //function pointer magic
        //Removes unnecessary lines above and below
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
        if (this->empty()) return 0;
        auto it = lower_bound(FN(x,0,true));
        return it->eval(x);
    }
};

const int maxn = 1e6+6;
int N;
struct Rec
{	
	ll x, y, a;
} recs[maxn];

ll dp[maxn];

int BUF=100000;
int buf_readed;
int buf_index;
char buffer[100000];
 
void my_init(){
    buf_index=buf_readed=0;
}
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

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    my_init();
    N = getInt();
    for (int i = 0; i < N; i++) {
        recs[i].x = getInt();
        recs[i].y = getInt();
        recs[i].a = getInt();
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
    	hull.addFN(FN(-recs[i].x,dp[i]));
    }
    cout << ans << '\n';

    return 0;
}