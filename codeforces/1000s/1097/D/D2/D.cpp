#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int M = 1e9+7;
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}
ll n;
int k;

gp_hash_table<ll,vector<ll>> facs;
ll dp[10005][2000];
ll inv[2000];

struct matrix {
  // N is the size of the matrix
  vector<vector<ll>> m;
  int N;
  matrix(int NN)
  {
     N = NN;
     for (int i = 0; i < N; i++) {
         m.push_back(vector<ll>(N,0));
     }
  }
  matrix operator * (matrix b)
  {
     matrix c = matrix(N);
     for (int i = 0; i < N; ++i)
       for (int j = 0; j < N; ++j)
         for (int k = 0; k < N; ++k) 
           c.m[i][j] = (c.m[i][j] + 1LL * m[i][k] * b.m[k][j]) % M;
     return c;
  }
};

matrix getunit(int N) {
    matrix x(N);
    for (int i = 0; i < N; i++) {
        x.m[i][i] = 1;
    }
    return x;
}

int cnt = 0;
matrix modPow(matrix m,int n, matrix& unit)
{
  cnt++;
  if ( n == 0 )
    return unit; // the unit matrix - that is 1 for principal diagonal , otherwise 0
  matrix half = modPow(m,n/2,unit);
  matrix out = half * half;
  if ( n % 2 )
    out = out * m;
  return out; 
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }
    vector<ll> factors;
    for (ll i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            if (i != n/i) factors.push_back(n/i);
            //cout << i << ' ' << n/i << '\n';
        }
    }
    sort(factors.begin(),factors.end());
    matrix cost(factors.size());
    for (int i = 0; i < factors.size(); i++) {
        //cout << i << ": ";
        ll ii = factors[i];
        for (int j = 0; j < factors.size(); j++) {
            ll jj = factors[j];
            if (ii % jj == 0) {
                facs[i].push_back(j);
                //cout << j << ' ';
            }   
        }
        //cout << '\n';
        dp[0][i] = ii;
        inv[i] = modexp(facs[i].size(),M-2);
        for (int j = 0; j < factors.size(); j++) {
            ll jj = factors[j];
            if (ii % jj == 0) {
                cost.m[i][j] = inv[i];
            }
            else cost.m[i][j] = 0;
        }
    }
   
    matrix u = getunit(factors.size());
    matrix ans = modPow(cost,k,u);
    ll tot = 0;
    for (int i = 0; i < factors.size(); i++) {
        tot = (tot + factors[i] * ans.m[factors.size()-1][i]) % M;
    }
    cout << cnt << '\n';
    cout << tot << '\n';
    return 0;
}

