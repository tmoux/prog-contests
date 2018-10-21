#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

map<pair<ll,int>,pair<ll,int>> mp;
pair<ll,int> gao(ll val, int mx) {
    if (val == 0) return {0,0};
    if (val < 10) {
        pair<ll,int> ans = {1,0};
        if (val < mx) ans.second = val - mx;
        return ans;
    }
    pair<ll,int> now = {val,mx};
    if (mp.find(now) != mp.end()) return mp[now];
    ll lim = 1;
    while (lim <= val/10) lim *= 10;
    pair<ll,int> ans = {0,0};
    while (true) {
        int newmx = mx;
        int dig = val / dig;
        if (dig > newmx) newmx = dig;
        pair<ll,int> tmp = gao(val % lim, newmx);
        ans.first += tmp.first;
        val -= val % lim;
        if (tmp.second < 0) val += tmp.second;
        else if (tmp.second == 0) {
            val -= newmx;
            if (newmx > 0) ans.first++;
        }
        if (dig == 0) break;
    }
    ans.second = val;
    return mp[now] = ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    mp.clear();
    ll n; cin >> n;
    cout << gao(n,0).first << '\n';

    return 0;
}
	

