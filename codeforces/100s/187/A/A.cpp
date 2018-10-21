#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n, A[maxn], B[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (A[ans] == B[i]) {
            ans++;
        }
    }
    cout << n-ans << '\n';



    return 0;
}
	

