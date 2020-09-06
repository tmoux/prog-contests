#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n;
int a[maxn];
int height[maxn];

ll dp[maxn][maxn];

ll f(int i, int h) {
    ll& res = dp[i][h];
    if (res != -1) return res;
    if (i == n) {
        return res = height[h];
    }
    ll add = max(0,height[h]-height[a[i]]); //need to add this no matter what
    res = f(i+1,a[i]); //do nothing, costs 0
    if (h < a[i]) {
        res = min(res,1+f(i+1,h)); //if prev is smaller, try setting to it's height, costs 1
    }
    res += add;
    //cout << "add = " << add << endl;
    //printf("[%d][%d]: %d\n",i,h,res);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> v;
    map<int,int> compress;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        v.push_back(a[i]);
    }
    int pt = 1;
    sort(v.begin(),v.end());
    for (int i: v) {
        if (compress.count(i)) continue;
        else {
            height[pt] = i;
            //cout << pt << ' ' << i << endl;
            compress[i] = pt++;
        }
    }
    for (int i = 0; i < n; i++) {
        a[i] = compress[a[i]];
    }
    memset(dp,-1,sizeof dp);
    ll ans = f(0,0);
    cout << ans << '\n';
}
