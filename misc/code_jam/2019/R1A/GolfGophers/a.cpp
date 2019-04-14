#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    int N, M; cin >> N >> M;
    for (int qq = 1; qq <= t; qq++) {
        vector<int> qs = {5,7,11,13,17,18};
        vector<int> res;
        for (int p: qs) {
            for (int i = 0; i < 18; i++) {
                cout << p;
                if (i < 17) cout << ' ';
                else cout << endl;
            }
            int r = 0;
            for (int i = 0; i < 18; i++) {
                int ai; cin >> ai;
                r += ai;
                r %= p;
            }
            res.push_back(r);
        }
        for (int m = 1; m <= 1000000; m++) {
            bool poss = true;
            for (int i = 0; i < 6; i++) {
                if (m % qs[i] != res[i]) {
                    poss = false;
                    break;
                }
            }
            if (poss) {
                cout << m << endl;
                int verdict; cin >> verdict;
                if (verdict == -1) exit(0);
                break;
            }
        }
    }
}

