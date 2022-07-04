#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, M = 1e9+7;
int n;

// given range [l, r), returns the first i s.t. f(i) is false
template <class Integer, class F>
Integer find_first_false(Integer l, Integer r, F &&f) {
  return *ranges::partition_point(ranges::views::iota(l, r), f);
}

int gcd(int a, int b) {
    if (a == 0 || b == 0) return a + b;
    return gcd(b,a%b);
}

int main()
{
    cin >> n;
    vector<int> perm(n);
    iota(begin(perm),end(perm),1);
    int mx = 0;
    int ans = 0;
    do {
        int gc = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int nc = gcd(gc,perm[i]);
            if (nc != gc) cnt++;
            gc = nc;
            // cout << gc << ' ';
        }
        // cout << '\n';
        // for (int i = 0; i < n; i++) {
        //     cout << perm[i] << ' ';
        // }
        // cout << ": " << cnt << '\n';
        if (cnt > mx) {
            mx = cnt;
            ans = 1;
        }
        else if (cnt == mx) {
            ans++;
        }
    } while (next_permutation(perm.begin(),perm.end()));


    printf("mx = %d, ans = %d\n",mx,ans);
}

