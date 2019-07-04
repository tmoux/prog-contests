#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 150005, maxm = 305;
int n, m, d;

ll dp[2][maxn];

struct Event
{
    int a, b;
};
map<int,vector<Event>> events;

struct MaxQueue
{
    deque<pair<ll,int>> q;
    int cnt_added = 0;
    int cnt_removed = 0;
    ll maximum() {
        assert(!q.empty());
        return q.front().first;
    }
    void push(ll new_element) { //add new element
        while (!q.empty() && q.back().first < new_element) {
            q.pop_back();
        }
        q.push_back({new_element,cnt_added});
        cnt_added++;
    }
    void pop() {
        if (!q.empty() && q.front().second == cnt_removed) {
            q.pop_front();
        }
        cnt_removed++;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> d;
    vector<int> times;
    for (int i = 0; i < m; i++) {
        int ai, bi, ti; cin >> ai >> bi >> ti;
        events[ti].push_back({ai,bi});    
        times.push_back(ti);
    }
    sort(times.begin(),times.end());
    times.erase(unique(times.begin(),times.end()),times.end());
    ll ans = -1e18;
    
    for (int i = 0; i < times.size(); i++) {
        int t = times[i];
        int td = i == 0 ? 0 : times[i]-times[i-1];
        int j = i&1;
        ll sum = 0;
        vector<Event> v;
        for (auto& e: events[t]) {
            sum += e.b - e.a;
            v.push_back(e);
        }
        int numSmaller = 0, numBigger = events[t].size();
        sort(v.begin(),v.end(),[](auto& a, auto& b) {
                return a.a > b.a;
                });
        MaxQueue q;
        int l = 1, r = 1; //interval [l,r)
        for (int p = 1; p <= n; p++) {
            while (!v.empty() && v.back().a <= p) {
                //flip it
                sum += 2 * v.back().a;
                numSmaller++;
                numBigger--;
                v.pop_back();
            }
            ll total = sum + 1LL*(numBigger-numSmaller)*p;
            //update maximum queue
            int lbound = max(1LL,p-1LL*d*td);
            int rbound = min(1LL*n,p+1LL*d*td);
            while (r <= rbound) {
                q.push(dp[j^1][r]);
                r++;
            }
            while (l < lbound) {
                q.pop();
                l++;
            }
            ll mx = q.maximum();
            dp[j][p] = total + mx;

            //update answer
            if (i == times.size()-1) {
                ans = max(ans,dp[j][p]);
            }
            //cout << times[i] << ' ' << p << ": " << dp[j][p] << '\n';
        }
    }
    cout << ans << '\n';
}

