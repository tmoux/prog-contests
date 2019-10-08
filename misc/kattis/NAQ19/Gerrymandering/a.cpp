#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int P, D;

int main() {
    cin >> P >> D;
    vector<pair<int,int>> district(D+1);
    int sum = 0;
    for (int i = 0; i < P; i++) {
        int d, a, b; cin >> d >> a >> b;
        district[d].first += a;
        district[d].second += b;
        sum += a + b;
    }
    int wa = 0, wb = 0;
    for (int i = 1; i <= D; i++) {
        int maj = (district[i].first+district[i].second)/2+1;
        if (district[i].first > district[i].second) {
            wb += district[i].second;
            wa += district[i].first - maj;
            cout << "A " << (district[i].first-maj) << ' ' << district[i].second << '\n';
        }
        else {
            wa += district[i].first;
            wb += district[i].second - maj;
            cout << "B " << district[i].first << ' ' << (district[i].second-maj) << '\n';
        }
    }
    double ans = (double)abs(wa-wb)/sum;
    cout << fixed << setprecision(10) << ans << '\n';
}

