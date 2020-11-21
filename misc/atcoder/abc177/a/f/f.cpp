#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int H, W;
int A[maxn], B[maxn];

int start[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        cin >> A[i] >> B[i];
        --A[i]; --B[i];
        //cout << i << ": " << A[i] << ' ' << B[i] << endl;
    }
    set<int> pos;
    multiset<int> ms;
    for (int i = 0; i < W; i++) {
        pos.insert(i);
        start[i] = i;
        ms.insert(i-start[i]);
    }
    for (int i = 0; i < H; i++) {
        if (pos.empty()) {
            cout << -1 << '\n';
        }
        else {
            int max_start = -1;
            auto it = pos.lower_bound(A[i]);
            for (; it != pos.end(); ) {
                if (*it <= B[i]) {
                    //cout << "deleting " << *it << endl;
                    auto p = ms.find(*it-start[*it]);
                    ms.erase(p);
                    max_start = max(max_start,start[*it]);
                    start[*it] = -1;
                    pos.erase(it++);
                }
                else break;
            }
            if (B[i]+1 < W && !pos.count(B[i]+1)) {
                pos.insert(B[i]+1);
                start[B[i]+1] = max(start[B[i]+1],max_start);
                ms.insert(B[i]+1-start[B[i]+1]);
            }

            /*
            cout << "i = " << i << endl;
            for (auto j: pos) {
                cout << j << ": start = " << start[j] << endl;
            }
            */

            if (ms.empty()) {
                cout << -1 << '\n';
            }
            else {
                cout << *ms.begin()+i+1 << '\n';
            }
        }
    }
}
