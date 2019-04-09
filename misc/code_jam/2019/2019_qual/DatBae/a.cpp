#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n, b, f; cin >> n >> b >> f;
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            p[i] = i % 32;
        }
        vector<int> ans(n);
        for (int i = 0; i < 5; i++) {
            string ask;
            for (int j = 0; j < n; j++) {
                ask += (char)(((p[j]>>i)&1)+'0');
            }
            cout << ask << '\n';
            fflush(stdout);
            string read;
            cin >> read;
            for (int j = 0; j < n - b; j++) {
                int x = read[j] == '0' ? 0 : 1;
                ans[j] += x * (1<<i);
            }
        }
        int prev = 31;
        vector<int> res;
        int index = 0;
        for (int i = 0; i < n - b; i++) {
            //cout << i << ": " << ans[i] << '\n';
            //cout << ans[i] << ' ' << prev << ' ' << index << '\n';
            if (ans[i] == (prev+1) % 32) {
                index++;
            }
            else {
                while ((prev+1)%32 != ans[i]) {
                    res.push_back(index);
                    //cout << "added " << index << '\n';
                    //cout << prev << ' ' << ans[i] << '\n';
                    index++;
                    prev = (prev+1) % 32;
                }
                index++;
            }
            prev = ans[i];
        }
        assert(res.size() == b);
        for (int i = 0; i < res.size(); i++) {
            cout << res[i];
            if (i == res.size()-1) {
                cout << '\n';
                fflush(stdout);
            }
            else {
                cout << ' ';
            }
        }
        int verdict; cin >> verdict;
        assert(verdict == 1);
        if (verdict == -1) return 0;
    }
}

