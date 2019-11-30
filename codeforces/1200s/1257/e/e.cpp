#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int k[3], n;
vector<int> a[3];

int cnt[3][maxn];

int sum(int i, int l, int r) {
    return cnt[i][r]-cnt[i][l-1];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> k[0] >> k[1] >> k[2];
    n = k[0] + k[1] + k[2];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < k[i]; j++) {
            int ai; cin >> ai;
            a[i].push_back(ai);
            cnt[i][ai]++;
        }
        sort(a[i].begin(),a[i].end());
        for (int j = 1; j <= n; j++) {
            cnt[i][j] += cnt[i][j-1];
        }
    }
    int ans = min(k[0]+k[1],min(k[1]+k[2],k[2]+k[0]));
    int zero_cnt = 0;
    int one_r = a[1].back();
    int pt = 0;
    for (int i = 1; i <= n; i++) {
        auto it = lower_bound(a[2].begin(),a[2].end(),i);
        int res = (i-zero_cnt-1) + (a[0].size()-zero_cnt);
        if (one_r >= i && it != a[2].end()) {
            int two_l = *it;
            /*
            printf("zero_cnt = %d, cur_res = %d\n",zero_cnt,res);
            printf("%d: one_r = %d, two_l = %d\n",i,one_r,two_l);
            */
            if (two_l < one_r) {
                int add = min(sum(1,two_l,one_r),sum(2,two_l,one_r));
                assert(add >= 0);
                res += add;
            }
        }
        //cout << i << ": " << res << '\n';
        ans = min(ans,res);
        if (pt < a[0].size() && a[0][pt] == i) {
            zero_cnt++;
            pt++;
        }
    }
    cout << ans << '\n';
}
