#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    cout << n << ' ' << q << '\n';
    set<pair<int,int>> edges;
    while (q--) {
        int r = rand() % 3;
        if (r == 0) {
            cout << "?\n";
        }
        else if (r == 1 || edges.empty()) {
            cout << "+ ";
            int a = rand() % n + 1;
            int b = rand() % n + 1;
            while (edges.count({a,b})) {
                a = (a+5) % n + 1;
                b = (b+7) % n + 1;
            }
            cout << a << ' ' << b << '\n';
            edges.insert({a,b});
        }
        else {
            cout << "- ";
            auto p = *edges.begin(); edges.erase(edges.begin());
            cout << p.first << ' ' << p.second << '\n';
        }
    }
}

