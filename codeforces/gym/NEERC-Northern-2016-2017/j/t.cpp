#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <complex>
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define pi acos(-1.0)
#define mem0(a) memset(a,0,sizeof(a))
#define memf(b) memset(b,false,sizeof(b))
#define ll long long
#define eps 1e-10
#define inf 1e17
#define maxn 101010
string str="a=? max ?\nb=a max a\nc=b max b\nd=c max c\ne=d max d\nf=e max e\ng=f max f\nh=g max g\ni=h max h\nj=i max i\nk=j max j\nl=k max k\nm=l/l\n";
int main()
{
    freopen("java2016.in","r",stdin);
    freopen("java2016.out","w",stdout);
    int n,i,j;
    cin>>n;
    if(n==0)
    {
        puts("?/?/?");
        return 0;
    }
    int nn=sqrt(n);
    string ans="n=m";
    for(int i=1;i<=nn-1;i++)
    {
        ans+="+m";
    }
    ans+="\n";
    ans+="n*n";
    for(int i=nn*nn+1;i<=n;i++)
    {
        ans+="+m";
    }
    ans+="\n";
    cout<<str<<ans;
    return 0;
}
