#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double eps = 1e-7;
const int maxn = 1005;
int n, m, A[maxn], B[maxn];

bool canMake(double fuel) {
    double mass = m + fuel;
    double firstTakeoff = (mass) / A[0];
    mass -= firstTakeoff;
    for (int i = 1; i < n; i++) {
        if (mass < m) return false;
        double landing = (mass) / B[i];
        mass -= landing;
        double takeoff = mass / A[i];
        mass -= takeoff;
    }
    //landing on earch
    if (mass < m) return false;
    double land = mass / B[0];
    mass -= land;
    return mass >= m;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    double lo = 0, hi = 1e9+1;
    if (!canMake(hi)) {
        cout << -1 << '\n';
        return 0;
    }
    while (lo + eps < hi) {
        double mid = (lo+hi)/2;
        if (canMake(mid)) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(10) << hi << '\n';


    return 0;
}
	

