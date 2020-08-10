#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pd = pair<ld,ll>;

const int maxn = 20;
ld p[4][maxn+1];
int n;

ll fac[maxn+1];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i-1] * i;
    for (int i = 0; i < 4; i++) {
        p[i][0] = 1;
        cin >> p[i][1];
        for (int j = 2; j <= n; j++) {
            p[i][j] = p[i][j-1] * p[i][1];
        }
    }
    priority_queue<pd,vector<pd>,greater<pd>> pq;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (i+j+k > n) continue;
                int l = n-i-j-k;
                ld prob = p[0][i]*p[1][j]*p[2][k]*p[3][l];
                ll cnt = fac[n]/fac[i]/fac[j]/fac[k]/fac[l];
                pq.push({prob,cnt});
            }
        }
    }
    ld sum = 0;
    while (!pq.empty()) {
        auto f = pq.top(); pq.pop();
        ld prob = f.first;
        ll cnt = f.second;
        if (cnt == 1) {
            if (pq.empty()) {
                //root of tree, stop
            }
            else {
                auto g = pq.top(); pq.pop();
                ld prob2 = g.first;
                ll cnt2 = g.second;

                sum += (prob+prob2);
                pq.push({prob+prob2,1});
                if (cnt2 > 1) pq.push({prob2,cnt2-1});
            }
        }
        else {
            sum += (cnt/2)*2*prob;
            pq.push({prob*2,cnt/2});
            if (cnt&1) {
                //odd one out
                pq.push({prob,1});
            }
        }
    }
    cout << fixed << setprecision(10) << sum << endl;
}
