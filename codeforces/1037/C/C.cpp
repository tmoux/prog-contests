#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+6;
int n;
string a, b;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a >> b;
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (i < n - 1 && a[i] != b[i] && a[i+1] != b[i+1] && a[i] != a[i+1]) {
            //swap them
            res++;
            i++;
        }
        else if (a[i] != b[i]) {
            res++;
        }
    }
    cout << res << '\n';

    return 0;
}

