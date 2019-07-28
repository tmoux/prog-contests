#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n;
int v[2*maxn];
int pre[2*maxn];

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
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i+n] = v[i];
    }
    pre[0] = v[0];
    for (int i = 1; i < 2*n; i++) {
        pre[i] = pre[i-1] + v[i];
    }
    int total = pre[n-1];
    MaxQueue mq;
    for (int i = n/2; i < n-1; i++) {
        mq.push(pre[i]-pre[i-n/2]);
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        mq.push(pre[i+n-1]-pre[i+n-1-n/2]);
        int maxSum = mq.maximum();
        res = max(res,total-maxSum);
        mq.pop();
    }
    cout << res << '\n';
}
