#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    set<int> s;
    for (int _ = 0; _ < n; _++) {
        int i = 1;
        for (;;i++) {
            if (!s.count(i)) break;
        }
        int j = 1;
        for (;;j++) {
            if (j != i && !s.count(j) && !s.count(i^j)) break;
        }
        vector<int> v = {i,j,i^j};
        //sort(v.begin(),v.end());
        for (int x = 0; x < 3; x++) {
            bitset<7> b(v[x]);
            //cout << b << ' ';
            cout << v[x] << ' ';
        }
        cout << '\n';

        s.insert(i);
        s.insert(j);
        s.insert(i^j);
    }
}
