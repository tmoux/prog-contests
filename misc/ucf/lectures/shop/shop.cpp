#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    ll ans = 0;
    if (n <= 3) {
        cout << max(max(A[1],A[2]),A[3]) << '\n';
        return 0;
    }
    priority_queue<int> q;
    if (n % 2 == 0) {
        ans += A[n];
        n--;
    }
    while (true) {
        if (n != 3) {
            q.push(A[n]);
            q.push(A[n-1]);
            ans += q.top();
            q.pop();
            n -= 2;
        }
        else if (n == 3) {
            q.push(A[n]);
            q.push(A[n-1]);
            q.push(A[n-2]);
            ans += q.top();
            q.pop();
            break;
        }
    }

    cout << ans << '\n';

    return 0;
}
	

