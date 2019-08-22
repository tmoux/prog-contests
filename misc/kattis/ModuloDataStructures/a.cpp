#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const int BLK = 350;
int N, Q;
int a[maxn];
int cnt[BLK+5][BLK+5];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int A, B, C; cin >> A >> B >> C;
            if (B < BLK) {
                cnt[B][A] += C;
            }
            else {
                for (; A <= N; A += B) {
                    a[A] += C;
                }
            }
        }
        else {
            int d; cin >> d;
            int ans = a[d];
            for (int i = 1; i < BLK; i++) {
                ans += cnt[i][d%i];
            }
            cout << ans << '\n';
        }
    }

}

