#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int n, bit[maxn], a[maxn];

int sum(int i) {
    int res = 0;
    while (i > 0) {
        res += bit[i];
        i -= i & (-i);
    }
    return res;
}

void add(int i, int x) {
    for (; i <= n; i += i & (-i)) {
        bit[i] += x;
    }
}

int adding[maxn], losing[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int inversions = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai; ai++;
        a[i] = ai;
        int r = sum(n) - sum(ai);
        inversions += r;
        add(ai,1);
        adding[i] = r;
        losing[i] = n - 1 - r;
    }
    int minInversions = inversions;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int r = inversions + (adding[i]-losing[i]) + (losing[j] - adding[j]);
            if (r < minInversions) {
                minInversions = r;
                cnt = 1;
            }
            else if (r == minInversions) {
                cnt++;
            }
        }
    }
    cout << minInversions << ' ' << cnt << '\n';

    return 0;
}

