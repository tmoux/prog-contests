#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, d;
ll m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> d;
    vector<pair<ll,int>> times(n);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        times[i] = {ai,i};
    }
    sort(times.begin(),times.end());
    int dayCount = 1;
    vector<int> ans(n);
    set<pair<ll,int>> days;
    for (auto p: times) {
        int ai = p.first;
        auto it = days.begin();
        if (!days.empty() && it->first <= ai) {
            ans[p.second] = it->second;
            days.insert({ai+d+1,it->second});
            days.erase(it);
        }
        else {
            ans[p.second] = dayCount;
            days.insert({ai+d+1,dayCount++});
        }
    }
    cout << days.size() << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}

