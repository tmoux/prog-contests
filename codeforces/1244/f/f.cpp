#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;

bool isBlock[maxn];
int dist[maxn];

int prev(int x) {
    return x == 0 ? n-1 : x-1;
}
int next(int x) {
    return x == n-1? 0 : x+1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    vector<int> a(n);
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        a[i] = s[i] == 'W';
    }
    memset(dist,-1,sizeof dist);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            if (a[n-1] == a[i] || a[i+1] == a[i])
                dist[i] = 0;
        }
        else if (i == n-1) {
            if (a[i-1] == a[i] || a[0] == a[i])
                dist[i] = 0;
        }
        else {
            if (a[i-1] == a[i] || a[i+1] == a[i])
                dist[i] = 0;
        }
        if (dist[i] == 0) {
            q.push(i);
        }
    }
    if (q.empty()) {
        //alternating
        for (int i = 0; i < n; i++) {
            if (k&1) {
                cout << (s[i]=='W'?'B':'W');
            }
            else {
                cout << s[i];
            }
        }
        cout << '\n';
        return 0;
    }
    while (!q.empty()) {
        int f = q.front(); q.pop();
        if (dist[prev(f)] == -1) {
            dist[prev(f)] = dist[f] + 1;
            q.push(prev(f));
        }
        if (dist[next(f)] == -1) {
            dist[next(f)] = dist[f] + 1;
            q.push(next(f));
        }
    }
    for (int i = 0; i < n; i++) {
        int K = min(k,dist[i]);
        if (K&1) {
            cout << (s[i]=='W'?'B':'W');
        }
        else {
            cout << s[i];
        }
    }
    cout << '\n';
}

