#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m;
int a[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < 10; i++) {
        int num1 = 0;
        int can1 = 0;
        vector<pair<bool,bool>> ps(n);
        for (int j = 0; j < n; j++) {
            bool has0 = false;
            bool has1 = false;
            for (int k = 0; k < m; k++) {
                if (a[j][k] & (1<<i)) {
                    has1 = true;
                }
                else has0 = false;
            }
            ps[j].first = has0;
            ps[j].second = has1;
            if (has1 && !has0) {
                num1++;
            }
            else if (has1 && has0) can1++;
        }
        if (num1&1) {
            cout << "TAK\n";
            for (int j = 0; j < n; j++) {
                int found = -1;
                for (int k = 0; k < m; k++) {
                    if (ps[j].first && !ps[j].second) {
                        if (a[j][k] & (1<<i)) {
                            found = a[j][k];
                            break;
                        }
                    }
                    else {
                        if (!(a[j][k] && (1<<i))) {
                            found = a[j][k];
                            break;
                        }
                    }
                }
                assert(found != -1);
                cout << found << ' ';
            }
            return 0;
        }
        else if (can1 > 0) {
            cout << "TAK\n";
            bool u1 = false;
            for (int j = 0; j < n; j++) {
                int found = -1;
                for (int k = 0; k < m; k++) {
                    if (ps[j].first && !ps[j].second) {
                        if (a[j][k] & (1<<i)) {
                            found = a[j][k];
                            break;
                        }
                    }
                    else if (u1 == false) {
                        if (a[j][k] & (1<<i)) {
                            found = a[j][k];
                            u1 = true;
                            break;
                        }
                    }
                    else {
                        if (!(a[j][k] & (1<<i))) {
                            found = a[j][k];
                            break;
                        }
                    }
                }
                assert(found != -1);
                cout << found << ' ';
            }
            return 0;
        }
    }
    cout << "NIE\n";
}

