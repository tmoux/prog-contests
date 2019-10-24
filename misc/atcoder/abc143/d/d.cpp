#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e3+3;
int n, l[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    sort(l,l+n);
    int ans = 0;
    for (int i = 0; i < n-2; i++) {
        int pt = i+2;
        for (int j = i+1; j < n; j++) {
            while (pt < n && l[pt] < l[i] + l[j]) pt++;
            ans += pt-(j+1);
            cout << i << ' ' << j << ": " << pt << '\n';
        }
    }
    cout << ans << '\n';
}

