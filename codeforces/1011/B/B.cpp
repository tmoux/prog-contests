#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, m, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int ai; cin >> ai;
        A[ai]++;
    }

    for (int days = 100; days >= 1; days--) {
        int numPeople = 0;
        for (int i = 1; i <= 100; i++) {
            numPeople += A[i]/days;
        }
        if (numPeople >= n) {
            cout << days << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';

    return 0;
}
	

