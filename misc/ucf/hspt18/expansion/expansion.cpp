#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int a = 1; a <= t; a++) {
        int o, n; cin >> o >> n;
        vector<int> orig(o), news(n);
        for (int i = 0; i < o; i++) cin >> orig[i];
        for (int i = 0; i < n; i++) cin >> news[i];
        sort(news.begin(),news.end());
        //go left to right greedy
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j: orig) {
                if (j <= news[i]) {
                    cnt++;
                }
            }
            if (cnt * 2 > orig.size()) {
                //add it
                ans++;
                orig.push_back(news[i]);
            }
            //cout << news[i] << ' ' << cnt << '\n';
        }
        printf("Expansion #%d: %d\n",a,ans);
    }

    return 0;
}

