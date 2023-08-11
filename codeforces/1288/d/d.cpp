#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m;
int a[maxn][10];
int b[maxn];

int valid[1<<10];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    int lo = 0, hi = 1e9+9;
    pair<int,int> ret;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        bool poss = false;
        pair<int,int> ans;
        //cout << "checking " << mid << endl;
        for (int j = 0; j < (1<<m); j++) valid[j] = -1;
        for (int i = 0; i < n; i++) {
            b[i] = 0;
            for (int j = 0; j < m; j++) {
                b[i] |= (a[i][j] < mid ? 0 : 1) << j;
            }
            //cout << i << ": " << b[i] << '\n';
            if (valid[b[i]] == -1) {
                for (int s = b[i]; ;s = (s-1)&b[i]) {
                    valid[s] = i;
                    //cout << "adding " << s << endl;
                    if (s == 0) break;
                }

                int f = ((1<<m)-1)^b[i];
                //cout << "f = " << f << endl;
                if (valid[f] != -1) {
                    poss = true;
                    ans = {i,valid[f]};
                    break;
                }
            }
        }
        //cout << mid << ": " << poss << endl;
        if (poss) {
            ret = ans;
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    cout << ret.first+1 << ' ' << ret.second+1 << '\n';
}

