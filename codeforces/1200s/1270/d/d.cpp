#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, k;
int a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    map<int,int> cnt;
    for (int i = 1; i <= k+1; i++) {
        cout << "? ";
        for (int j = 1; j <= k+1; j++) {
            if (j == i) continue;
            cout << j << ' ';
        }
        cout << endl;
        int pos, val; cin >> pos >> val;
        cnt[val]++;
    }
    auto p = *cnt.rbegin();
    cout << "! ";
    cout << p.second << endl;
}

