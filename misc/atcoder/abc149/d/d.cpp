#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, k;
int R, S, P;
string t;
char play[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    cin >> R >> S >> P;
    cin >> t;
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        string r;
        for (int j = i; j < n; j += k) {
            r += t[j];
        }
        bool good = true;
        for (int j = 0; j < r.size(); j++) {
            if (!good) {
                good = true;
            }
            else {
                if (r[j] == 'r') ans += P;
                else if (r[j] == 's') ans += R;
                else if (r[j] == 'p') ans += S;
                if (j < r.size()-1 && r[j] == r[j+1]) {
                    good = false;
                }
            }
        }
        //cout << ans << endl;
    }
    cout << ans << '\n';
}

