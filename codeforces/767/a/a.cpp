#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool has[100005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int pt = n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        has[ai] = true;
        while (pt >= 1 && has[pt]) {
            cout << pt << ' ';
            pt--;
        }
        cout << '\n';
    }
}

