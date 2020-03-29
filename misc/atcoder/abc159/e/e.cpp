#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int h, w, k;
int a[11][1005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> h >> w >> k;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char c; cin >> c;
            a[i][j] = c-'0';
        }
    }
    int ans = 2e9;
    for (int mask = 0; mask < (1<<h); mask++) {
        int cut = 0;
        vector<bool> v;
        for (int i = 0; i < h; i++) {
            v.push_back(mask&(1<<i));
        }
        vector<int> cnt;
        vector<int> comp(h);
        int pt = 0;
        for (int i = 0; i < v.size(); i++) {
            if (i > 0 && v[i] != v[i-1]) {
                cut++;
                pt++;
            }
            comp[i] = pt;
        }
        ++pt;
        cnt.resize(pt);
        for (int i = 0; i < w; i++) {
            vector<int> add(pt);
            for (int j = 0; j < h; j++) {
                if (a[j][i]) add[comp[j]]++;
            }
            for (int j = 0; j < pt; j++) {
                if (add[j] > k) {
                    goto cont;
                }
            }
            bool flag = false;
            for (int j = 0; j < pt; j++) {
                if (cnt[j] + add[j] > k) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                //cut here
                for (int j = 0; j < pt; j++) {
                    cnt[j] = add[j];
                }
                cut++;
            }
            else {
                for (int j = 0; j < pt; j++) {
                    cnt[j] += add[j];
                }
            }
        }
        ans = min(ans,cut);
        //cout << mask << "; " << cut << '\n';
        cont: ;
    }
    cout << ans << '\n';
}

