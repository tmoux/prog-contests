#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, a[maxn];
vector<int> divs[maxn];

bool comp[maxn];

int cnt[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int gc = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        gc = __gcd(gc,a[i]);
    }
    for (int i = 1; i <= 1000000; i++) {
        divs[i].reserve(30);
    }
    for (int i = 2; i <= 1000000; i++) {
        if (!comp[i]) {
            for (int j = i; j <= 1000000; j += i) {
                divs[j].push_back(i);
                if (j > i) comp[i] = true;
            }
        }
    }
    bool isPairwise = true;
    for (int i = 0; i < n; i++) {
        for (auto d: divs[a[i]]) {
            if (++cnt[d] > 1) {
                isPairwise = false;
                break;
            }
        }
    }

    if (isPairwise) {
        cout << "pairwise coprime\n";
    }
    else if (gc == 1) {
        cout << "setwise coprime\n";
    }
    else {
        cout << "not coprime\n";
    }
}
