#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

const ll maxn = 200005;
ll n;
ll freq[maxn];
map<ll,pair<ll,ll>> pts;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    ll idx = 0;
    for (ll i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        pts[a].first++;
        pts[b].second++;
    }   

    ll curr = 0;
    ll prev = -1;
    for (auto p: pts) {
        ll pos = p.first;
       
        if (prev != -1) {
            freq[curr] += (pos - prev - 1);
            //cout << pos << ' ' << "invl: " << (pos - prev - 1) << '\n';
        }
        curr += p.second.first;
        freq[curr]++;
        //cout << pos << ' ' << "End: " << curr << '\n';
        curr -= p.second.second;
        prev = pos;
    }

    for (ll i = 1; i <= n; i++) {
        cout << freq[i] << ' ';
    }

    return 0;
}
	

