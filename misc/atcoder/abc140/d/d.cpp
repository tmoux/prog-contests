#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, K;
string s;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K >> s;
    int pt = 0;
    while (K--) {
        if (pt >= N-1) break;
        while (pt + 1 < N && s[pt+1] == s[pt]) pt++;

        char orig = s[pt];
        int start = pt+1;
        pt = start;
        while (pt+1 < N && s[pt+1] == s[pt]) pt++;
        for (int j = start; j <= pt; j++) {
            s[j] = orig;
        }
        //cout << K << ": " << s << '\n';
    }
    int sum = 0;
    for (int i = 1; i < N; i++) {
        if (s[i] == s[i-1]) sum++;
    }
    cout << sum << '\n';
}

