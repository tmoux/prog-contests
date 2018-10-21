#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

const ll M = 1e9+7;
map<int,int> factors;
ll ans = 0;

void factor(int i) {
    if (i == 1) return;
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            while (i % j == 0) {
                factors[j]++;
                i /= j;
            }
            factor(i);
            return;
        }
    }
    //must be prime
    factors[i]++;
}


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        factor(ai);
    }
    vector<pair<int,int>> ps;
    for (auto p: factors) {
        ps.push_back(p);
    }
    ll ans = 1;
    for (auto p: ps) {
        ll mult = 1;
        ll res = 0;
        for (int i = 0; i <= p.second; i++) {
            res = (res + mult) % M;
            mult = (mult * p.first) % M;
        }
        ans = (ans * res) % M;
    }
    cout << ans << '\n';

    return 0;
}
	

