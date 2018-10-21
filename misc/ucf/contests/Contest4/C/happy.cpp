#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

map<ll,int> mp;
//maps mask to frequency?
int q;

ll getMask(const string& s) {
    ll res = 0;
    int cnt = 0;
    for (int i = s.size() - 2; i >= 0; i--) {
        if (s[i] > s[i+1]) {
            res |= (1LL << cnt);
            cnt++;
        }
    }
    return res;
}

ll get(ll s) {
    ll res = 0;
    int cnt = 0;
    while (s) {
        if (s % 10) {
            res |= (1LL << cnt);
        }
        s /= 10;
        cnt++;
    }
    return res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            string s; cin >> s;
            ll add = getMask(s);
            mp[add]++;
        }
        else if (t == 2) {
            ll rem; cin >> rem;
            mp[get(rem)] = 0;
        }
        else if (t == 3) {
            ll rem; cin >> rem;
            cout << mp[get(rem)] << '\n';
        }
    }

    return 0;
}
	

