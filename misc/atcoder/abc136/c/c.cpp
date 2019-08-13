#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N;
int H[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }
    bool poss = true;
    for (int i = N - 2; i >= 0; i--) {
        if (H[i] <= H[i+1]) {
            continue;
        }
        else {
            H[i]--;
            if (H[i] > H[i+1]) {
                poss = false;
                break;
            }
        }
    }
    cout << (poss ? "Yes" : "No") << '\n';
}

