#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const int maxn = 105;
int n;
ld a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(9);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 1) {
            cout << 1 << '\n';
            return 0;
        }
    }
    sort(a,a+n,[](auto a, auto b) { return a > b; });
    ld S = 0;
    ld P = 1;
    for (int i = 0; i < n && S < 1; i++) {
        S += a[i]/(1-a[i]);
        P *= (1-a[i]);
        //cout << S << ' ' << P << '\n';
    }
    cout << (S*P) << '\n';


    return 0;
}

