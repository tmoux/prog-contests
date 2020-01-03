#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
pair<ll,ll> invl[maxn];
ll a[maxn];

struct Event
{
    bool isQuery;
    bool isStart; //1 = start, 0 = end;
    ll x;
    int id;

    //start, query, end
    int eval() {
        if (!isQuery) {
            return isStart ? 0 : 2;    
        }
        return 1;
    }
};

ll R[maxn];

int ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> invl[i].first >> invl[i].second;
    }
    vector<Event> v;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        v.push_back({1,0,a[i],i+1});
    }
    for (int i = 1; i < n; i++) {
        ll l = invl[i].first-invl[i-1].second;
        ll r = invl[i].second-invl[i-1].first;
        R[i] = r;
        v.push_back({0,1,l,i});
        v.push_back({0,0,r,i});
    }
    sort(v.begin(),v.end(),[](auto a, auto b) {
        if (a.x != b.x) return a.x < b.x;
        return a.eval() < b.eval();
            });
    set<pair<ll,int>> ms; //(r,id)
    int cnt = 0;
    for (auto e: v) {
        if (e.isQuery) {
            if (!ms.empty()) {
                //grab one with smallest r and use it
                auto p = *ms.begin();
                ms.erase(ms.begin());
                ans[p.second] = e.id;
                cnt++;
            }
        }
        else {
            if (e.isStart) {
                ms.insert({R[e.id],e.id});
            }
            else {
                ms.erase({R[e.id],e.id});
            }
        }
    }
    if (cnt != n-1) {
        cout << "No\n";
    }
    else {
        cout << "Yes\n";
        for (int i = 1; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}

