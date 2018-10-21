#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, m, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int left = m;
    for (int i = 0; i < n; i++) {
        if (A[i] < left) {
            left -= A[i];
            cout << 0 << ' ';
        }
        else {
            int used = 1;
            A[i] -= left;
            used += A[i] / m;
            left = m - (A[i] % m);
            cout << used << ' ';
        }
    }

    return 0;
}
	

