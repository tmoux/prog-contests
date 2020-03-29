#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, m;
int a[maxn];
vector<int> v[maxn];

int cnt(int l, int r, int x) {
    auto it = lower_bound(v[x].begin(),v[x].end(),l);
    auto it2 = upper_bound(v[x].begin(),v[x].end(),r);
    return distance(it,it2);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    random_device device;
    mt19937 gen(device());
    */
    srand(time(NULL));
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        v[a[i]].push_back(i);
    }
    while (m--) {
        int l, r; cin >> l >> r;
        --l; --r;
        int len = r-l+1;
        int target = len/2+1;
        bool done = false;
        for (int _ = 0; _ < max(25,len/10000); _++) {
            int ran = (rand()%len)+l;
            if (cnt(l,r,a[ran]) >= target) {
                cout << a[ran] << '\n';
                done = true;
                break;
            }
        }
        /*
        for (int i = l; i <= r; i++) {
            if (cnt(l,r,a[i]) >= target) {
                cout << a[i] << '\n';
                done = true;
                break;
            }
        }
        */
        if (!done) {
            cout << 0 << '\n';
        }
    }
}
