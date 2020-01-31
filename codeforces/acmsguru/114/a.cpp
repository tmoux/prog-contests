#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 15005;
int n;
vector<pair<int,int>> v;

double calc(double x) {
    double res = 0;
    for (auto p: v) {
        res += p.second*abs(x-p.first);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, p; cin >> x >> p;
        v.push_back({x,p});
    }
    double lo = 0, hi = 50005;
    for (int qq = 0; qq < 600; qq++) {
        double m1 = lo + (hi-lo)/3, m2 = hi - (hi-lo)/3;
        if (calc(m1) < calc(m2)) {
            hi = m2;
        }
        else lo = m1;
    }
    cout << fixed << setprecision(5) << lo << endl;
}

