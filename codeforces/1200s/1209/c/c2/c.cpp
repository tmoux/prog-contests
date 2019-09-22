#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
int d[maxn];
int is1[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        string s; cin >> s;
        for (int i = 0; i < n; i++) {
            is1[i] = false;
        }
        for (int i = 0; i < n; i++) {
            d[i] = s[i] - '0';
        }
        bool done = false;
        for (int di = 0; di < 10; di++) {
            if (done) break;
            //di is starting digit for second num
            bool flag = true;
            int max1 = 0, max2 = di;
            for (int i = 0; i < n; i++) {
                if (d[i] >= max2) {
                    is1[i] = false;
                    max2 = d[i];
                }
                else if (di >= d[i] && d[i] >= max1) {
                    is1[i] = true;
                    max1 = d[i];
                }
                else {
                    flag = false;
                    /*
                    cout << "breaking " << di << "at " << i << '\n';
                    cout << "max1 = " << max1 << ", max2 = " << max2 << '\n';
                    */
                    break;
                }
            }
            /*
            cout << di << ":\n";
            for (int i = 0; i < n; i++) {
                cout << (is1[i] ? 1 : 2); 
            }
            cout << '\n';
            */
            assert(max1 <= di);
            if (!flag) {
                continue;
            }
            else {
                done = true;
                for (int i = 0; i < n; i++) {
                    cout << (is1[i] ? 1 : 2);
                }
                cout << '\n';
            }
        }
        if (done) continue;
        else {
            cout << "-\n";
        }
    }

}

