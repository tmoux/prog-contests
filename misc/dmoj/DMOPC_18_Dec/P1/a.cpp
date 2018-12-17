#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int K; cin >> K;
    double mx; cin >> mx;
    double sum = 0;
    for (int a = 0; a < K; a++) {
        int t; cin >> t;
        double r = mx;
        while (t--) {
            double s; cin >> s;
            r += s;
        }
        sum += r;
    }
    double ans = sum/(double)(K);
    cout << fixed << setprecision(7) << ans << '\n';

    return 0;
}

