#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int a[32];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    int cnt = 0;
    for (int i = 0; i <= 31; i++) {
        if (n & (1<<i)) {
            a[i]++;
            cnt++;
        }
    }
    for (int i = 31; i > 0; i--) {
        int mov = max(0,min(a[i],(k-cnt)));
        a[i] -= mov;
        a[i-1] += mov*2;
        cnt += mov;
        /*
        cout << i << ' ' << cnt << '\n';
        for (int j = 0; j < 5; j++) {
            cout << a[j] << ' ';
        }
        cout << '\n';
        */
    }
    vector<int> ans;
    for (int i = 0; i <= 31; i++) {
        for (int j = 0; j < a[i]; j++) {
            ans.push_back(1<<i);
        }
    }
    if (ans.size() == k) {
        cout << "YES\n";
        for (int j: ans) {
            cout << j << ' ';
        }
        cout << '\n';
    }
    else {
        cout << "NO\n";
    }

    return 0;
}

