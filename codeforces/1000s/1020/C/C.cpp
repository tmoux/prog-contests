#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3005;
const ll INF = 1e18;
int n, m;
map<int,vector<int>> mp;

ll getSmall(multiset<int>& ms, int k, multiset<int>& every, vector<int>& addback) {
    ll res = 0;
    for (auto it = ms.begin(); it != ms.end() && k > 0; ++it) {
        res += (ll)(*it);
        every.erase(every.find(*it));
        addback.push_back(*it);
        k--;
    }
    return res;
}

ll getEvery(multiset<int>& ms, int k) {
    ll res = 0;
    for (auto it = ms.begin(); it != ms.end() && k > 0; ++it) {
        res += (ll)(*it);
        k--;
    }
    return res;
}

vector<pair<int,multiset<int>>> alls;
multiset<int> every;
int num1 = 0;
int maxSize;

ll f(int target) {
    if (target <= 0 || target > maxSize + 1) return INF;
    ll res = 0;
    int taken = num1;
    vector<int> adds;
    for (int j = alls.size() - 1; j >= 0; j--) {
        if (alls[j].first < target) break;
        int take = alls[j].first - target + 1;
        res += getSmall(alls[j].second,take,every,adds);
        taken += take;
    }
    if (taken < target) {
        int need = target - taken;
        if (need > every.size()) {
            for (int i: adds) {
                every.insert(i);
            }
            return INF;
        }
        res += getEvery(every,need);
    }
    for (int i: adds) {
        every.insert(i);
    }
    return res;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int pi, ci; cin >> pi >> ci;
        if (pi != 0 && ci > 0) mp[pi].push_back(ci);
        else num1++;
    }

    maxSize = 0; int maxNum = -1;
    for (auto p: mp) {
        if (p.second.size() > maxSize) {
            maxSize = p.second.size();
            maxNum = p.first;
        }
    }

    if (num1 > maxSize) {
        cout << 0 << '\n';
        return 0;
    }
    //now we know we have to greedy it
    
    for (auto p: mp) {
        multiset<int> ms;
        for (int i: p.second) {
            ms.insert(i);
            every.insert(i);
        }
        alls.push_back({p.second.size(),ms});
    }
    sort(alls.begin(),alls.end());

    int lo = 0, hi = maxSize+2;
    while (true) {
        int mid = (lo+hi)/2;
        //cout << lo << ' ' << mid << '\n';
        if (f(mid) <= f(mid-1) && f(mid) <= f(mid+1)) {
            //cout << f1 << ' ' << f2 << ' ' << f3 << '\n';
            cout << f(mid) << '\n';
            return 0;
        }
        else if (f(mid-1) < f(mid) && f(mid) < f(mid+1)) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    /*
    for (int i = -1; i < maxSize + 3; i++) {
        cout << i << ' ' << f(i) << '\n';
    }
    */


    return 0;
}
	

