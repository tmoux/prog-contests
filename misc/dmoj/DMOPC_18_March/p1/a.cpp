#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[4];
int inn[4];;
vector<int> dir[4];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    for (int i = 1; i <= 3; i++) {
        cin >> a[i];
        if (a[i] != 0) {
            dir[a[i]].push_back(i);
            inn[i]++;
        }
    }
    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 1; j <= 3; j++) {
            if (inn[j] == 0) {
                cnt++;
                for (int a: dir[j]) {
                    inn[a]--;
                }
                inn[j] = -1;
            }
        }
    }
    cout << (cnt == 3 ? "YES" : "NO") << '\n';
}
