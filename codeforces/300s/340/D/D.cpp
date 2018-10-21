#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n, A[maxn];
vector<int> T;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    //setup T
    T.resize(n+1);
    fill(T.begin(),T.end(),maxn);
    T[0] = 0;
    //input
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(T.begin(),T.end(),A[i]);
        ans = max(ans,(int)distance(T.begin(),it)); 
        *it = A[i]; 
    }
    cout << ans << '\n';
    
    return 0;
}