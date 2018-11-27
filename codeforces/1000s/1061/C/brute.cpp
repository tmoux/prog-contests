#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int cnt = 0;
    for (int i = 1; i < (1<<n); i++) {
        vector<int> idx;
        for (int j = 0; j < 10; j++) {
            if (i & (1 << j)) {
                idx.push_back(j);
            }
        }
        bool poss = true;
        for (int j = 0; j < idx.size(); j++) {
            if (a[idx[j]] % (j+1) != 0) {
                poss = false;
                break;
            }
        }
        if (poss) cnt++;
    }
    cout << cnt << '\n';


    return 0;
}

