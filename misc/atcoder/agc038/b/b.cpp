#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N, K, P[maxn];
int a[maxn];

int inc[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }
    inc[0] = 1;
    for (int i = 1; i < N; i++) {
        if (P[i] > P[i-1]) {
            inc[i] = inc[i-1] + 1;
        }
        else inc[i] = 1;
        //cout << i << ": " << inc[i] << '\n';
    }
    set<int> s;
    int ans = 0;
    int numSorted = 0;

    if (inc[K-1] >= K) numSorted++;
    else ans++;

    for (int i = 0; i < K; i++) {
        s.insert(P[i]);
    }
    for (int i = 0; i + K < N; i++) {
        if (inc[i+K] >= K) {
            numSorted++;
        }
        else {
            /*
            cout << "set: ";
            for (int j: s) {
                cout << j << ' ';
            }
            cout << '\n';
            printf("P[i] = %d, min = %d, max = %d, P[i+K] = %d\n",P[i],*s.begin(),P[i+K],*s.rbegin());
            */
            if (P[i] <= *s.begin() && P[i+K] > *s.rbegin()) {

            }
            else {
                ans++;
            }
        }
        s.erase(P[i]);
        s.insert(P[i+K]);
        //cout << i << ": " << ans << ' ' << numSorted << '\n';
    }
    if (numSorted > 0) ans++;
    cout << ans << '\n';
    /*
    for (int i = 0; i + K <= N; i++) {
        for (int j = 0; j < N; j++) {
            a[j] = P[j];
        }
        sort(a+i,a+i+K);
        for (int j = 0; j < N; j++) {
            cout << a[j] << ' ';
        }
        cout << '\n';
    }
    */
}
