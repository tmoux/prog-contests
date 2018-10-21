#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;

const int maxt = 1000005;
int t, A[maxt];
int M, x;

void primeFactor(int n, map<int,int>& primes) {
    if (n == 1) return;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                primes[i]++;
                n /= i;
            }
            primeFactor(n,primes);
            return;
        }
    }
    primes[n]++;
}

void getFactors(vector<int>& res, vector<pair<int,int>>& ps, int i, int curr=1) {
    if (i == ps.size()) {
        res.push_back(curr);
        return;
    }
    int mult = 1;
    for (int j = 0; j <= ps[i].second; j++) {
        getFactors(res,ps,i+1,mult*curr);
        mult *= ps[i].first;
    }
}

bool tryGrid(int r, int c, pair<int,int> source) {
    vector<vector<int>> grid(r+5,vector<int>(c+5,-1));
    vector<int> check(maxt);
    queue<pair<int,int>> q;
    
    q.push(source);
    check[0]++;
    
    grid[source.first][source.second] = 0;
    
    while (!q.empty()) {
        pair<int,int> f = q.front();
        pair<int,int> dxy[] = {{-1,0},{1,0},{0,-1},{0,1}};
        for (int i = 0; i < 4; i++) {
            pair<int,int> newp = {f.first+dxy[i].first,f.second+dxy[i].second};
            if (newp.first >= 0 && newp.first < r && newp.second >= 0 && newp.second < c && grid[newp.first][newp.second] == -1) {
                grid[newp.first][newp.second] = grid[f.first][f.second] + 1;
                check[grid[newp.first][newp.second]]++;
                q.push(newp);
            }
        }
        q.pop();
    }
    
    //check if possible
    for (int i = 0; i <= M; i++) {
        if (check[i] != A[i]) {
            return false;
        }
    }
    //output answer;
    cout << r << ' ' << c << '\n';
    cout << source.first+1 << ' ' << source.second+1 << '\n';
    return true;
        
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> t;
    for (int i = 0; i < t; i++) {
        int a; cin >> a;
        A[a]++;
        M = max(M,a);
    }
    //check valid
    if (A[0] != 1 || A[1] > 4) {
        cout << -1 << '\n';
        return 0;
    }
    if (t == 1 && A[0] == 1) {
        cout << "1 1\n1 1\n";
        return 0;
    }
    map<int,int> primes;
    vector<pair<int,int>> ps;
    primeFactor(t,primes);
    for (auto p: primes) {
        ps.push_back(p);
    }
    vector<int> factors;
    getFactors(factors,ps,0);
    sort(factors.begin(),factors.end());
    //calculate x
    x = 0;
    for (int i = 1; i <= M; i++) {
        if (A[i] != (i) * 4) {
            x = i;
            break;
        }
    }
    //Now we know the source is at (x, M - x)
    for (int r: factors) {
        int c = t / r;
        int y = c - x;
        int xx = M - y;
        if (y >= 0 && y < c && xx >= 0 && x < r && tryGrid(r,c,{xx,y})) return 0; 
    }
    cout << -1 << '\n';
    
    
    return 0;
}
