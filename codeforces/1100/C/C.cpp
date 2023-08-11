#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld PI = 3.14159265358979323846;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, r; cin >> n >> r;
    ld x = 2*PI/n; //in radians
    ld num = sqrt(2)*sqrt(-r*r*(cos(x)-1))+r*(-cos(x))+r;
    ld den = cos(x) + 1;
    ld R = num/den;
    //cout << num << ' ' << den << '\n';
    cout << fixed << setprecision(10) << R << '\n';

    return 0;
}