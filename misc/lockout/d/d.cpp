#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, w, h;
const int maxn = 5005;
pair<pair<int,int>,int> a[maxn];

int dp[maxn];
int previous[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> w >> h;
    for (int i = 0; i < n; i++) {
        int ww, hh; cin >> ww >> hh;
        a[i] = {{ww,hh},i+1};
    }
    sort(a,a+n);
    for (int i = n-1; i >= 0; i--) {
        dp[i] = 1;
        previous[i] = i;
        for (int j = i+1; j < n; j++) {
            if (a[i].first.first < a[j].first.first && a[i].first.second < a[j].first.second) {
                int tr = 1+dp[j];
                if (tr > dp[i]) {
                    dp[i] = tr;
                    previous[i] = j;
                }
            }
        }
    }
    pair<int,int> best = {-1,-1};
    for (int i = 0; i < n; i++) {
        if (w < a[i].first.first && h < a[i].first.second) {
            best = max(best,{dp[i],i});
        }
    }
    if (best.first == -1) {
        cout << 0 << endl;
    }
    else {
        for (int i = 0; i < n; i++) {
            //cout << i << ": " << previous[i] << endl;
        }
        cout << best.first << endl;
        int cur = best.second;
        while (true) {
            cout << a[cur].second << ' ';
            int nx = previous[cur];
            if (nx == cur) break;
            cur = nx;
        }
        cout << '\n';
    }
}
