#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
//2 rows, 2 cols:
//row[r1]+row[r2]+col[c1]+col[c2]
//-a[r1][c1]
//-a[r1][c2]
//-a[r2][c1]
//-a[r2][c2]

ll accum(priority_queue<ll,vector<ll>,greater<ll>>& pq) {
    ll res = 0;
    while (!pq.empty()) {
        res += pq.top();
        pq.pop();
    }
    return res;
}

struct mx2 {
    ll a = 0, b = 0; //a >= b
    void insert(ll x) {
        if (x <= b) return;
        else if (x <= a) b = x;
        else {
            b = a;
            a = x;
        }
    }
    ll sum() {
        return a + b;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    bool swp = false;
    if (n > m) {
        swp = true;
    }
    vector<vector<int>> a(min(n,m));
    for (int i = 0; i < min(n,m); i++) {
        a[i] = vector<int>(max(n,m));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!swp) cin >> a[i][j];
            else cin >> a[j][i];
        }
    }
    if (swp) swap(n,m);
    //n <= m
    vector<ll> rowSum(n), colSum(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rowSum[i] += a[i][j];
            colSum[j] += a[i][j];
        }
    }
    priority_queue<ll,vector<ll>,greater<ll>> pq;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        pq.push(rowSum[i]);
        if (pq.size() > 4) pq.pop();
    }
    ans = max(ans,accum(pq));

    assert(pq.empty());
    for (int i = 0; i < m; i++) {
        pq.push(colSum[i]);
        if (pq.size() > 4) pq.pop();
    }
    ans = max(ans,accum(pq));

    //1 row, 3 cols
    assert(pq.empty());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            colSum[j] -= a[i][j];
        }
        for (int j = 0; j < m; j++) {
            pq.push(colSum[j]);
            if (pq.size() > 3) pq.pop();
        }
        for (int j = 0; j < m; j++) {
            colSum[j] += a[i][j];
        }
        ans = max(ans,rowSum[i]+accum(pq));
    }

    //1 col, 3 rows
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            rowSum[i] -= a[i][j];
        }
        for (int i = 0; i < n; i++) {
            pq.push(rowSum[i]);
            if (pq.size() > 3) pq.pop();
        }
        for (int i = 0; i < n; i++) {
            rowSum[i] += a[i][j];
        }
        ans = max(ans,colSum[j]+accum(pq));
    }

    //2 rows, 2 cols
    for (int r1 = 0; r1 < n; r1++) {
        for (int r2 = r1+1; r2 < n; r2++) {
            for (int j = 0; j < m; j++) {
                colSum[j] -= a[r1][j];
                colSum[j] -= a[r2][j];
            }
            mx2 mx;
            for (int j = 0; j < m; j++) {
                mx.insert(colSum[j]);
            }
            for (int j = 0; j < m; j++) {
                colSum[j] += a[r1][j];
                colSum[j] += a[r2][j];
            }
            ll tr = rowSum[r1] + rowSum[r2];
            tr += mx.sum();
            ans = max(ans,tr);
        }
    }

    cout << ans << '\n';
}
