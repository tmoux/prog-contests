#include <iostream>
#include <cstdio>
 
using namespace std;
const int NMAX = 2014;
long long d1[2*NMAX], d2[2*NMAX], sol[2];
pair < int , int > v[2];
int a[NMAX][NMAX];
inline void Update(const int c,const int i,const int j,const long long val){
    if(val > sol[c]){
        sol[c] = val;
        v[c].first = i;
        v[c].second = j;
    }
}
int main(){
    cin.sync_with_stdio(false);
    int n;
    cin >> n;
    sol[0] = sol[1] = -1; 
    for(int i = 1;i <= n; ++i)
        for(int j = 1;j <= n; ++j){
            int x;
            cin >> a[i][j];
            d1[i+j] += a[i][j];
            d2[i-j+n] += a[i][j];
        }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            Update((i+j)&1,i,j,d1[i+j]+d2[i-j+n]-a[i][j]);
    cout<<sol[0]+sol[1]<<"\n";
    if(v[0] > v[1])
        swap(v[0],v[1]);
    cout<<v[0].first<<" "<<v[0].second<<" ";
    cout<<v[1].first<<" "<<v[1].second<<"\n";
    return 0;
}
