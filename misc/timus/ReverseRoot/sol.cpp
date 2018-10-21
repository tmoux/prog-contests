#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a;
    vector<double> b;
    while (cin >> a) {
    	b.push_back((double)(sqrt(a)));
    }
    reverse(b.begin(),b.end());
    for (double i: b) cout << fixed << setprecision(5) << i << '\n';

    return 0;
}