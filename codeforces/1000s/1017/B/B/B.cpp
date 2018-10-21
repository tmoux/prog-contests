#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;
int A[maxn][2];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    string s; cin >> s;
    int numZeros = 0, numEmpty, numOnesVal = 0, numOnes2 = 0;
    for (int i = 0; i < n; i++) {
        A[i][0] = s[i]-'0';
    }
    cin >> s;
    for (int i = 0; i < n; i++) {
        A[i][1] = s[i]-'0';
    }

    for (int i = 0; i < n; i++) {
        if (A[i][0] == 0 && A[i][1] == 0) {
            numEmpty++;
        }
        else if (A[i][0] == 0 && A[i][1] == 1) {
            numZeros++;
        }
        else if (A[i][0] == 1 && A[i][1] == 1) {
            numOnesVal++;
        }
        else if (A[i][0] == 1 && A[i][1] == 0) {
            numOnes2++;
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (A[i][0] == 0 && A[i][1] == 0) {
            ans += numOnesVal + numOnes2;
        }
        else if (A[i][0] == 0 && A[i][1] == 1) {
            ans += numOnes2;
        }
        else if (A[i][0] == 1 && A[i][1] == 1) {
            ans += numEmpty;
        }
        else if (A[i][0] == 1 && A[i][1] == 0) {
            ans += numEmpty + numZeros;
        }
    }
    ans /= 2;
    cout << ans << '\n';



    return 0;
}
