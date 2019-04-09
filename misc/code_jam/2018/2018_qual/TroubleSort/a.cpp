#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        int N; cin >> N;
        vector<int> a(N), s(N);
        multiset<int> p[2];
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            s[i] = a[i];
            p[i&1].insert(a[i]);
        }
        sort(s.begin(),s.end());
        bool ok = true;
        for (int i = 0; i < N; i++) {
            if (p[i&1].count(s[i])) {
                auto it = p[i&1].find(s[i]);
                p[i&1].erase(it);
            }
            else {
                cout << i << '\n';
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << "OK\n";
        }
    }
}
