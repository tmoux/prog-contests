#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, x; cin >> N >> x;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    int res = 0;
    for (int i = 0; i < N; i++) {
        if ((i != N - 1 && a[i] <= x) || (i == N - 1 && a[i] == x)) {
            res++;
            x -= a[i];
        }
    }
    cout << res << '\n';

    return 0;
}

