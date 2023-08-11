#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int floor(int x) {
    if (x < 0) return x/2-1;
    return x/2;
}

int ceil(int x) {
    if (x < 0) return x/2;
    return x/2+1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a;
    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (ai % 2 == 0) {
            cout << ai/2 << '\n';
        }
        else {
            if (cnt&1) {
                cout << floor(ai) << '\n';
            }
            else {
                cout << ceil(ai) << '\n';
            }
            cnt++;
        }
    }
}

