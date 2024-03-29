#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        switch (ai) {
            case 4:
                a[i] = 0;
                break;
            case 8:
                a[i] = 1;
                break;
            case 15:
                a[i] = 2;
                break;
            case 16:
                a[i] = 3;
                break;
            case 23:
                a[i] = 4;
                break;
            case 42:
                a[i] = 5;
                break;
        }
    }
    vector<vector<int>> last(6);
    int ngood = 0;
    for (int i = 1; i <= n; i++) {
        //cout << i << ": " << a[i] << '\n';
        if (a[i] == 0) {
            last[a[i]].push_back(i);
        }
        else {
            if (last[a[i]-1].empty()) continue;
            else {
                last[a[i]].push_back(i);
                last[a[i]-1].pop_back();

                if (a[i] == 5) {
                    ngood += 6;
                }
            }
        }
    }
    cout << (n-ngood) << '\n';
}

