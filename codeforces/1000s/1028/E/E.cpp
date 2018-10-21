#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 150000;
int n, B[maxn], A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    bool allSame = true;
    int maxNum = -1, maxPos;
    for (int i = 1; i <= n; i++) {
        cin >> B[i];
        if (i > 1 && B[i] != B[i-1]) allSame = false;
    }
    for (int i = 1; i <= n; i++) {
        if (B[i] >= maxNum) {
            maxNum = B[i];
            if (B[i] > B[(i+n)%n+1]) {
                maxPos = i;
            }
        }
    }
    if (allSame) {
        if (B[1] == 0) {
            cout << "YES" << '\n';
            for (int i = 1; i <= n; i++) {
                cout << 1 << ' ';
            }
        }
        else {
            cout << "NO\n";
        }
        return 0;
    }
    else {
        int idx = maxPos;
        A[idx] = B[idx];
        for (int i = 0; i < n - 1; i++) {
            idx = (idx+n-2)%n+1;
            int next = (idx)%n+1, prev = (idx-2+n)%n+1;
            //cout << prev << ' ' << idx << ' ' << next << '\n';
            A[idx] = B[idx] + (B[prev] - B[idx])/A[next] * A[next];
            while (A[idx] <= B[prev]) {
                A[idx] += A[next];
            }
        }

        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << A[i] << ' ';
        }
    }

    return 0;
}
	

