#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
int lastIndex[10];
int d[maxn];
bool is1[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        string s; cin >> s;
        for (int i = 0; i < n; i++) {
            d[i] = s[i] - '0';
        }
        memset(lastIndex,-1,sizeof lastIndex);
        for (int i = n-1; i >= 0; i--) {
            if (lastIndex[d[i]] != -1) continue;
            else lastIndex[d[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            is1[i] = false;
        }
        int max1 = 0;
        int pt = 0;
        for (int digit = 0; digit < 10; digit++) {
            if (lastIndex[digit] == -1) continue;
            while (pt < n && pt <= lastIndex[digit]) {
                if (d[pt] == digit) {
                    is1[pt] = true;
                    max1 = digit;
                }
                pt++;
            }
        }
        bool flag = true;
        //check if the others are nondecreasing
        int mn = 0;
        int min2 = 9;
        for (int i = 0; i < n; i++) {
            if (is1[i]) continue;
            min2 = min(min2,d[i]);
            if (d[i] < mn) {
                flag = false;
                break;
            }
            else {
                mn = d[i];
            }
        }
        //cout << max1 << ' ' << min2 << '\n';
        flag &= (max1 <= min2);
        if (flag) {
            for (int i = 0; i < n; i++) {
                cout << (is1[i] ? 1 : 2);
            }
            cout << '\n';
        }
        else {
            cout << "-\n";
        }
    }

}

