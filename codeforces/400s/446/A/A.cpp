#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, A[maxn], longest[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    int ans = 0;
    for (int i = n; i >= 1; i--) {
        if (i == n) longest[i] = 1;
        else {
            longest[i] = (A[i+1] > A[i] ? longest[i+1] + 1 : 1);
        }
        ans = max(ans,min(longest[i]+1,n));
    }

    for (int i = 1; i <= n; i++) {
        int end = i + longest[i] - 1;
        int seglen = 0;
        if (A[end+2] >= A[end] + 2) {
            seglen = max(seglen,longest[i] + 1 + longest[end+2]);
        }
        if (longest[i] == 1 || A[end-1] + 2 <= A[end+1]) {
            seglen = max(seglen,longest[i] +longest[end+1]);
        }
        ans = max(ans,seglen);
        //cout << i << ' ' << seglen << '\n';
    }
    cout << ans << '\n';

    return 0;
}
	

