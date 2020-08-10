#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pd = pair<double,int>;
#define all(x) begin(x), end(x)
int n, w, t1, t2;
double u, v;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> w >> u >> v >> t1 >> t2;
    vector<pd> V;
    V.push_back({t1,0});
    V.push_back({t2,0});
    for (int i = 0; i < n; i++) {
        char ci; int mi; cin >> ci >> mi;
        while (mi--) {
            int l, p; cin >> l >> p;
            if (ci == 'W') p *= -1;
            //cout << (-p/u*w(i)/v) << endl;
            V.push_back({-p/u-w*(i+1)/v,1});
            V.push_back({-(p-l)/u-w*i/v,-1});
        }
    }
    sort(all(V));
    double ans = 0; int cur = 0;
    for (int i = 0; i < V.size(); i++) {
        cur += V[i].second;
        if (cur == 0 && t1 <= V[i].first && V[i].first < t2) {
            ans = max(ans,V[i+1].first-V[i].first);
        }
    }
    cout << fixed << setprecision(10) << ans << '\n';
}
