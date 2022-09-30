//ulimit -s unlimited
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<long long>
#define vi vector<int>
#define vb vector<bool>
#define pql priority_queue<long long>
#define pqp priority_queue<pair<ll,ll> >
#define pqs priority_queue<ll,vl,greater<ll> >
#define md ((ll) 1e9+7)

string s;
ll dp[2001][2001];

ll rec(ll i,ll j){
    if(i == j-1){
        if(s[i] != s[j]){
            return 1;
        }
        return 3;
    }
    else if(dp[i][j] != -1){
        return dp[i][j];
    }
    else{
        ll ii = rec(i+2,j);
        if(ii == 3){
            if(s[i]<s[i+1]){
                ii = 1;
            }
            else if(s[i]>s[i+1]){
                ii = 2;
            }
        }
        ll jj = rec(i,j-2);
        if(jj == 3){
            if(s[j]<s[j-1]){
                jj = 1;
            }
            else if(s[j]>s[j-1]){
                jj = 2;
            }
        }
        ll ij = rec(i+1,j-1);
        if(ij == 3){
            if(s[i] != s[j]){
                ij = 1;
            }
        }
        if((ii == 1 && ij == 1) || (jj == 1 && ij == 1)){
            dp[i][j] = 1;
        }
        else if((ii == 2 || ij == 2) && (jj == 2 || ij == 2)){
            dp[i][j] = 2;
        }
        else{
            dp[i][j] = 3;
        }
        return dp[i][j];
    }
}

void solve(){
    s.clear();

    ll i,j,k,n,m;
    cin>>s;
    n = s.length();
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            dp[i][j] = -1;
        }
    }
    ll ans = rec(0,n-1);

    if(ans == 1){
        cout<<"Alice\n";
    }
    else if(ans == 2){
        cout<<"Bob\n";
    }
    else{
        cout<<"Draw\n";
    }

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    //t = 1;
    while(t--)
        solve();
    return 0;
}
