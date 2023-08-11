#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, A[105];
int p[105];

int main()
{
    //ios_bas::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        p[A[i]]++;
        ans = max(ans,p[A[i]]);
    }
    cout << ans << '\n';


    return 0;
}
	

