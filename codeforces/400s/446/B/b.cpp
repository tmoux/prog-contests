#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005, maxk = 1e6+6;
int n, m, k, p, a[maxn][maxn];
ll row_sum[maxn], col_sum[maxn];

ll row_ans[maxk], col_ans[maxk];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k >> p;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            row_sum[i] += a[i][j];
            col_sum[j] += a[i][j];
        }
    }
    ll ans = -1e18;
    priority_queue<ll> row_pq, col_pq;
    for (int i = 0; i < n; i++) {
        row_pq.push(row_sum[i]);
    }
    ll curr = 0;
    for (int i = 1; i <= k; i++) {
        ll add = row_pq.top();
        curr += add;
        row_pq.pop();
        row_pq.push(add-1LL*m*p);
        row_ans[i] = curr;
        //cout << i << ": "  << row_ans[i] << '\n';
    }
    for (int i = 0; i < m; i++) {
        col_pq.push(col_sum[i]);
    }
    curr = 0;
    for (int i = 1; i <= k; i++) {
        ll add = col_pq.top();
        curr += add;
        col_pq.pop();
        col_pq.push(add-1LL*n*p);
        col_ans[i] = curr;
        //cout << i << ": "  << col_ans[i] << '\n';
    } 
    for (int i = 0; i <= k; i++) {
        ll sum = row_ans[i] + col_ans[k-i];
        sum -= 1LL*i*p*(k-i);
        //cout << i << ": " << sum << '\n';
        ans = max(ans,sum);
    }
    cout << ans << '\n';
}
