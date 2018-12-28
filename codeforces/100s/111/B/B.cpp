#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;
int used[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int j = 1; j <= n; j++) {
        int xi, yi; cin >> xi >> yi;
        int res = 0;
        for (int i = 1; i*i <= xi; i++) {
            if (xi % i == 0) {
                if (used[i] < j-yi) res++;
                used[i] = j;
                if (xi/i == i) continue;
                if (used[xi/i] < j-yi) res++;
                used[xi/i] = j;
            }
        }
        cout << res << '\n';
    }

    return 0;
}

