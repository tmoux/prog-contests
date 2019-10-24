#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5+5;
int n, k;

struct Event
{
    bool start;
    int t, id;
};

int l[N], r[N];

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    vector<Event> events;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        events.push_back({true,l[i],i});
        events.push_back({false,r[i],i});
    }
    sort(events.begin(),events.end(),[](auto a, auto b) {
            if (a.t != b.t) return a.t < b.t;
            if (a.start != b.start) return (int)(a.start) > (int)(b.start);
            return r[a.id] > r[b.id];
            });
    set<pair<int,int>> rights; //current right points {t,id}
    vector<int> ans;
    for (Event e: events) {
        if (!e.start) {
            auto it = rights.find({e.t,e.id});
            if (it != rights.end())
                rights.erase(it);
        }
        else {
            rights.insert({r[e.id],e.id});
            if (rights.size() > k) {
                auto it = prev(rights.end());
                ans.push_back(it->second);
                rights.erase(it);
            }
        }
    }
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << (i+1) << ' ';
    }
    cout << '\n';
}

