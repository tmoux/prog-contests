#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;
int a[maxn], b[maxn], t[maxn];
int get(int a, int b, int t) {
    for (int t2 = 0; t2 < 4; t2++) {
        if ((t | t2) == a && (t & t2) == b) {
            return t2;
        }
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> b[i];
    }
    bool poss;
    for (int j = 0; j < 4; j++) {
        poss = true;
        t[1] = j;
        for (int i = 1; i < n; i++) {
            t[i+1] = get(a[i],b[i],t[i]);
            if (t[i+1] == -1) {
                poss = false;
                break;
            }
        }
        if (poss) {
            cout << "YES\n";
            for (int i = 1; i <= n; i++) {
                cout << t[i] << ' ';
            }
            return 0;
        }
    }
    cout << "NO\n";

    
    return 0;
}
