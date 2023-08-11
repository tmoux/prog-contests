#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int askA(int x) {
    cout << "A " << x << endl;
    int y; cin >> y;
    return y;
}

int askB(int x) {
    cout << "B " << x << endl;
    int y; cin >> y;
    return y;
}

void answer(int x) {
    cout << "C " << x << endl;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    set<int> mine, yours;
    int k1; cin >> k1;
    for (int i = 0; i < k1; i++) {
        int ai; cin >> ai;
        mine.insert(ai);
    }
    int k2; cin >> k2;
    for (int i = 0; i < k2; i++) {
        int ai; cin >> ai;
        yours.insert(ai);
    }
    int p = askB(*yours.begin());
    if (mine.count(p)) {
        answer(p);
        return;
    }
    else {
        queue<int> q;
        q.push(p);
        vector<bool> seen(n+1,false);
        int nxt;
        while (!q.empty()) {
            int f = q.front();
            if (mine.count(f)) {
                nxt = f;
                break;
            }
            seen[f] = true;
            for (int j: adj[f]) {
                if (seen[j]) continue;
                seen[j] = true;
                q.push(j);
            }
            q.pop();
        }
        int p2 = askA(nxt);
        if (yours.count(p2)) {
            answer(nxt);
            return;
        }
        else {
            answer(-1);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();

    return 0;
}

