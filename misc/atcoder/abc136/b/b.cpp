#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int numDigits(int x) {
    int res = 0;
    while (x) {
        res++;
        x /= 10;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        if (numDigits(i) % 2 == 1) ans++;
    }
    cout << ans << '\n';
}

