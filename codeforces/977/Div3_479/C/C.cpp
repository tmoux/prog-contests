#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n, k;
int arr[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr,arr+n);
    if (k == 0) {
        if (arr[0] > 1) {
            cout << arr[0]-1 << '\n';
        }
        else {
            cout << "-1\n";
        }
        return 0;
    }
    int ans = arr[k-1];
    if (k != n && arr[k] == ans) {
        cout << "-1\n";
        return 0;
    }
    cout << ans << '\n';

    return 0;
}
	

