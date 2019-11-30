#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> rate(n+1), weight(m+1);
    for (int i = 1; i <= n; i++) {
        cin >> rate[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> weight[i];
    }
    vector<int> garage(n+1,0);
    queue<int> q;
    ll ans = 0;
    for (int i = 0; i < 2*m; i++) {
        int ai; cin >> ai;
        if (ai > 0) {
            //check if it's empty
            bool found = false;
            for (int j = 1; j <= n; j++) {
                if (garage[j] == 0) {
                    garage[j] = ai;
                    found = true;
                    break;
                }
            }
            if (!found) {
                q.push(ai);
            }
        }
        else {
            ai *= -1;
            int pos = -1;
            //cout << "looking to empty " << ai << endl;
            for (int j = 1; j <= n; j++) {
                if (garage[j] == ai) {
                    ans += rate[j]*weight[ai];
                    pos = j;
                    garage[j] = 0;
                    break;
                }
            }
            assert(pos != -1);
            if (!q.empty()) {
                int f = q.front(); q.pop();
                garage[pos] = f;    
            }
        }
    }
    cout << ans << '\n';
}

