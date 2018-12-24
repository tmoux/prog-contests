#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n << ' ' << n << '\n';
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i+1;
    }
    random_shuffle(a.begin(),a.end());
    for (int i: a) cout << i << ' '; cout << '\n';
    random_shuffle(a.begin(),a.end());
    for (int i: a) cout << i << ' '; cout << '\n';
    for (int i = 0; i < n; i++) {
        int t = rand() % 2;
        if (t == 0) {
            cout << 1 << ' ';
            int l1 = rand() % n + 1;
            int l2 = rand() % n + 1;
            int r1 = rand() % n + 1;
            int r2 = rand() % n + 1;
            if (l1 > r1) swap(l1,r1);
            if (l2 > r2) swap(l2,r2);
            cout << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << '\n';
        }
        else {
            cout << 2 << ' ';
            int l = rand() % n + 1;
            int r = rand() % n + 1;
            while (r == l) {
                r = rand() % n + 1;
            }
            cout << l << ' ' << r << '\n';
        }
    }

    return 0;
}

