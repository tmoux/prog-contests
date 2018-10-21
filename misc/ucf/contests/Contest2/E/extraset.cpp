#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

ll hasht(const vector<int>& vec) {
    ll mult = 1;
    ll res = 0;
    for (int i: vec) {
        res += i * mult;
        mult *= 3;
    }
    return res;
}

map<ll,ll> occ;
int cards[100005][20];

int other(int a, int b) {
    if (a == b) return a;
    return 3 - a - b;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int k, n;
    cin >> k >> n;
    for (int i = 0; i < n; i++) {
        vector<int> v(k);
        for (int j = 0; j < k; j++) {
            cin >> v[j];
            cards[i][j] = v[j];
        }
        occ[hasht(v)]++;
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            vector<int> newvec(k);
            for (int a = 0; a < k; a++) {
                newvec[a] = other(cards[i][a],cards[j][a]);
            }
            if (occ.count(hasht(newvec))) ans++;
            /*
            cout << i << ' ' << j << '\n';
            for (int a: newvec) {
                cout << a << ' ';
            }
            cout << '\n';
            */
        }
    }
    cout << ans/3 << '\n';


    return 0;
}
	

