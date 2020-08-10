#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

struct MinQueue
{
    deque<pair<ll,int>> q;
    int cnt_added = 0;
    int cnt_removed = 0;
    ll minimum() {
        assert(!q.empty());
        return q.front().first;
    }
    void push(ll new_element) { //add new element
        while (!q.empty() && q.back().first > new_element) {
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int iter = 1; iter <= t; iter++) {
        cout << "Case #" << iter << ": ";
        int n, m; cin >> n >> m;
        vector<ll> c(n), dp(n);
        for (int i = 0; i < n; i++) {
            cin >> c[i];
            if (i == 0) c[i] = 0;
            else if (c[i] == 0) c[i] = INF;
        }
        MinQueue mq;
        //cout << '\n';
        for (int i = 0; i < n; i++) {
            ll cost = i == 0 ? 0 : mq.minimum();
            dp[i] = cost;
            //cout << i << ": " << dp[i] << '\n';
            mq.push(min(INF,cost+c[i]));
            if (i-m >= 0) mq.pop();
        }
        cout << (dp[n-1]==INF?-1:dp[n-1]) << '\n';
    }
}
