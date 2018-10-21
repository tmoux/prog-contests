#include <bits/stdc++.h>
#define rep(i,n) for(auto i=0; i<(n); i++)
#define mem(x,val) memset((x),(val),sizeof(x));
#define write(x) freopen(x,"w",stdout);
#define read(x) freopen(x,"r",stdin);
#define all(x) x.begin(),x.end()
#define sz(x) ((int)x.size())
#define sqr(x) ((x)*(x))
#define pb push_back
#define clr clear()
#define inf (1<<30)
#define ins insert
#define xx first
#define yy second
#define eps 1e-9
using namespace std;
typedef long long ll ;
typedef pair<ll,ll> ii;
typedef pair<ll,ii> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<string> vs;
typedef map<ll,ll> mii;
typedef map<string,ll> msi;
typedef set<ll> si;
typedef set<string> ss;

ll MAX=300000;
ll n,m;
vi a(MAX);
vi st(4*MAX);

ll left(ll p){return(p<<1);}
ll right(ll p){return (p<<1)+1;}

void  build(ll p,ll l,ll r){
    if(l==r){st[p]=0; return;}
    build(left(p),l,(l+r)/2);
    build(right(p),(l+r)/2+1,r);
    st[p]=0;
    return;
}

void  update( ll val,ll i,ll j,ll p=1,ll l=0,ll r=n-1){
 //   cout<< " node "<<p<<" i "<<i<<"j "<<j<<" l "<<l<<" r "<<r<<endl;
    if(i>r||j<l) {return;}
    if(l>=i&&r<=j){
            if(st[p]==(r-l)+1){return;}
            if(l==r){a[l]=val,st[p]=1; return;}
    }
     update(val,i,j,left(p),l,(l+r)/2);
     update(val,i,j,right(p),(l+r)/2+1,r);
     st[p]=st[left(p)]+st[right(p)];
        return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    //freopen("knight.in","r",stdin);
    cin.tie(0);

    cin>>n>>m;
    build (1,0,n-1);
    rep(b,m){
        ll i,j,k;
        cin>>i>>j>>k;
        ll i1=i-1,j1=k-2;
        ll i2=k,j2=j-1;
        //cout<< " frm "<<i1<<" to "<<j1<< " and "<<i2 << "to "<<j2<<endl;
      if(i1<=j1)
      update(k,i1,j1);
      if(i2<=j2)
      update(k,i2,j2);

    }
    rep(i,n){

        cout<<a[i]<<" ";
    }
    cout<<endl;

    return 0;
}