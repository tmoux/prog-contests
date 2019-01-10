#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int a[maxn][2];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    map<int,int> cnt;
    map<int,int> up; //number that are up
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        cnt[a[i][0]]++;
        if (a[i][0] != a[i][1]) cnt[a[i][1]]++;
        up[a[i][0]]++;
    }
    int need = (n+1)/2;
    int ans = maxn;
    for (auto& p: cnt) {
        if (p.second >= need) {
            //should only happen like 4 times
            int x = max(0,need-up[p.first]);
            ans = min(ans,x);
        }
    }
    cout << (ans == maxn ? -1 : ans) << '\n';


    return 0;
}
