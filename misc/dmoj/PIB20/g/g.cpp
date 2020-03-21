#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50005;
int N, a[maxn], pos[maxn];
int ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //subtask 1
    cin >> N;
    multiset<int> v;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        pos[a[i]] = i;
        v.insert(a[i]);
    }
    int d = 0;
    for (int i = 0; i < N; i++) {
        for (int fi: v) {
            int dd = abs(i-pos[fi]);
            if (__gcd(d,dd) == 1) {
                continue;
            }
            else {
                d = __gcd(d,dd);
                ans[i] = fi;
                auto it = v.find(fi);
                v.erase(it);
                break;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        cout << ans[i] << " \n"[i==N-1];
    }
}
