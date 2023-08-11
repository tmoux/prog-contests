#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 300005;
ll n, x, y;
vector<int> adj[maxn];
bool isMid[maxn];
ll subtree[maxn];

void markifMid(int i, int par) {
   for (int j: adj[i]) {
       if (j != par) {
           markifMid(j,i);
           isMid[i] |= isMid[j];
       }
   }
}

ll countSubtree(int i, int par) {
    subtree[i] = 1;
    for (int j: adj[i]) {
        if (j != par && !isMid[j]) {
            subtree[i] += countSubtree(j,i);
        }
    }
    return subtree[i];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //input
    cin >> n >> x >> y;
    isMid[x] = true; isMid[y] = true;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    markifMid(x,-1);
    ll s1 = countSubtree(x,-1);
    ll s2 = countSubtree(y,-1);
    
    //output answer
    ll total = n*(n-1);
    ll invalid = s1*s2;
    ll ans = total - invalid;
    cout << ans << '\n';

   

    return 0;
}
	

