#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 705;
bool poss[2][maxn*maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    vector<int> a(N);
    int sum = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (N <= 20) {
        //no shame
        int answer = 999999999;
        for (int i = 0; i < (1 << N); i++) {
            int rr = 0;
            for (int j = 0; j < N; j++) {
                if (i & (1 << j)) {
                    rr += a[j];
                }
            }
            answer = min(answer,abs(rr-(sum-rr)));
        }
        cout << answer << '\n';
        return 0;
    }
    poss[0][a[0]] = true;
    poss[0][0] = true;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= 700*N; j++) {
            poss[1][j] = true;
            if (poss[0][j] && (j+a[i]) * 2 <= maxn*N/2) {
                poss[1][j+a[i]] = true;
            }
        }
        for (int j = 0; j <= 700*N; j++) {
            poss[0][j] = poss[1][j];
            poss[1][j] = false;
        }
    }
    int ans = 999999999;
    for (int j = 1; j <= 700*N; j++) {
        if (poss[0][j]) ans = min(ans,abs(j-(sum-j)));
    }
    cout << ans << '\n';
    return 0;
}

