#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, A[maxn];
bool vis[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= n; i++) {
        memset(vis,0,sizeof(vis));
        vis[i] = true;
        int curr = i;
        while (true) {
            curr = A[curr];
            if (vis[curr]) {
                cout << curr << ' ';
                break;
            }
            vis[curr] = true;
        }
    }

    return 0;
}
	

