#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, a[105];
int b[105];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    ll sum = 0;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        b[i] = a[i];
        sum += a[i];
    }
    ll ans = 0;
    for (int i = 0; i < (1<<N); i++) {
        vector<int> xs;
        for (int j = 0; j < N; j++) {
            if (i&(1<<j)) xs.push_back(j+1);
        }
        ll sub = 0;
        for (int x: xs) {
            for (int j = x; j <= N; j += x) {
                sub += a[j];
                a[j] = 0;
            }
        }
        ans = max(ans,sum-sub);
        /*
        for (int x: xs) {
            cout << x << ' ';
        }
        cout << ": " << sub << '\n';
        */
        for (int j = 1; j <= N; j++) {
            a[j] = b[j];
        }
    }
    cout << ans << '\n';
}

