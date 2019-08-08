#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, a[maxn];
bool seen[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    int pt = n-1;
    while (pt >= 0) {
        ans++;
        //cout << pt << '\n';
        int prev = a[pt--];
        seen[prev] = true;
        while (true) {
            if (prev-1 == 0) break;
            if (seen[prev-1]) {
                prev--;
                continue;
            }
            else {
                if (a[pt] == prev-1) {
                    seen[prev-1] = true;
                    prev--;
                    pt--;
                    continue;
                }
                else {
                    break;
                }
            }
        }
    }
    cout << ans << '\n';
}
