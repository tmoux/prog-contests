#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    map<int,int> cnt;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        cnt[ai]++;
    }
    int ans = 0;
    for (auto p: cnt) {
        cout << p.first << ": " << p.second << '\n';
    }
    
    for (auto p: cnt) {
        int i = p.first;
        if (cnt.count(i+1) && cnt.count(i+2)) {
            int add = min(p.second,min(cnt[i+1],cnt[i+2]));
            cnt[i] -= add;
            cnt[i+1] -= add;
            cnt[i+2] -= add;
            ans += add;
        }
        ans += cnt[i]/3;
    }
    /*
    for (auto& p: cnt) {
        //cout << p.first << ": " << p.second << '\n';
        int add = p.second/3;
        ans += add;
        p.second %= 3;
    }
    */
    cout << ans << '\n';


    return 0;
}

