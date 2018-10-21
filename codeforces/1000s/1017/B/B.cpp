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
    int n00 = 0, n01 = 0, n10 = 0, n11 = 0;
    for (int i = 0; i < n; i++) {
        A[i][0] = (int)(s[i]-'0');
    }
    cin >> s;
    for (int i = 0; i < n; i++) {
        A[i][1] = (int)(s[i]-'0');
    }

    for (int i = 0; i < n; i++) {
        if (A[i][0] == 0 && A[i][1] == 0) {
            n00++;
        }
        else if (A[i][0] == 0 && A[i][1] == 1) {
            n01++;
        }
        else if (A[i][0] == 1 && A[i][1] == 1) {
            n11++;
        }
        else if (A[i][0] == 1 && A[i][1] == 0) {
            n10++;
        }
    }

    ll ans = (ll)(n00)*n11 + (ll)(n00) * n10 + (ll)(n10) * n01;
    cout << ans << '\n';



    return 0;
}
	

