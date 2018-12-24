#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, M, C, a[maxn];

bool check(int x) {
    int cows = 1;
    int curr = 0;
    int time = a[0];
    for (int i = 0; i < N; i++) {
        if (a[i] - time <= x && curr < C) {
            curr++;
        }
        else {
            cows++;
            curr = 1;
            time = a[i];
        }
    }
    return cows <= M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("convention.in","r",stdin); freopen("convention.out","w",stdout);
    cin >> N >> M >> C;
    for (int i = 0; i < N; i++) cin >> a[i];
    sort(a,a+N);
    int lo = -1, hi = 1000000500;
    while (lo + 1 < hi) {
        int m = (lo+hi)/2;
        (check(m)?hi:lo) = m;
    }
    cout << hi << '\n';
    return 0;
}
