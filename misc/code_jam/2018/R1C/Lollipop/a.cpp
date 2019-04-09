#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int t; cin >> t;
    while (t--) {
        int N; cin >> N;
        vector<bool> used(N);
        vector<int> cnt(N);
        for (int i = 0; i < N; i++) {
            int D; cin >> D;
            if (D == -1) exit(0);
            vector<int> prefs;
            for (int j = 0; j < D; j++) {
                int ai; cin >> ai;
                cnt[ai]++;
                if (!used[ai]) prefs.push_back(ai);
            }
            sort(prefs.begin(),prefs.end(),[&cnt](auto a, auto b) {
                    return cnt[a] < cnt[b];
                    });
            bool found = false;
            for (int j: prefs) {
                if (!used[j]) {
                    used[j] = true;
                    cout << j << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << -1 << endl;
            }
        }
    }

}

