#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> A(n+1);
    string s; cin >> s;
    for (int i = 1; i <= n; i++) {
        A[i] = s[i-1] - '0';
        A[i] += A[i-1];
    }
    if (A[n] == 0) {
        cout << "YES" << '\n';
        return 0;
    }
    for (int i = 1; i < n; i++) {
        if (A[i] == 0) continue;
        if (A[n] % A[i] == 0 && A[i] < A[n]) {
            bool poss = true;
            for (int j = A[i]; j <= A[n]; j += A[i]) {
                if (find(A.begin(),A.end(),j) == A.end()) {
                    poss = false;
                    break;
                }
            }
            if (poss) {
                cout << "YES\n";
                return 0;
            }
        }
    }
    cout << "NO\n";

    return 0;
}

