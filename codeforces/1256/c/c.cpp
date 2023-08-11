#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m, d;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> d;
    vector<int> c(m);
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }
    vector<int> ans(n+1,0);
    int pt = n;
    for (int i = m-1; i >= 0; i--) {
        for (int j = 0; j < c[i]; j++) {
            ans[pt--] = i+1;
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    */
    int pos = 0;
    while (pos <= n) {
        if (pos+d > n) {
            //done
            break;
        }
        else if (ans[pos+d] != 0) {
            pos += d;
        }
        else {
            //bring segment to the left
            pair<int,int> which = {-1,-1};
            for (int i = pos+1; i <= n; i++) {
                if (ans[i] != 0) {
                    which = {ans[i],i};
                    break;
                }
            }
            if (which.first == -1) {
                //impossible
                cout << "NO\n";
                return 0;
            }
            else {
                int len = 0;
                for (int i = which.second; i <= n && ans[i] == which.first; i++) {
                    len++;
                    ans[i] = 0;
                }
                for (int i = pos+d; i < pos+d+len; i++) {
                    ans[i] = which.first;
                }
                pos = pos+d+len-1;
            }
        }
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

