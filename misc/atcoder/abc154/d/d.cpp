#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 200005;
int N, K, p[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> p[i];
        ++p[i];
    }
    int cur = 0;
    for (int i = 0; i < K; i++) {
        cur += p[i];
    }
    int ans = cur;
    for (int i = 0; i+K < N; i++) {
        cur -= p[i];
        cur += p[i+K];
        ans = max(ans,cur);
    }
    cout << fixed << setprecision(10) << (double)(ans)/2 << endl;
}

