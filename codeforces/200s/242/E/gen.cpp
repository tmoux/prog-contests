#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    int n, q; cin >> n >> q;
    srand(time(NULL));
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << (rand() % 10) << ' ';
    }
    cout << '\n';
    cout << q << '\n';
    for (int i = 0; i < q; i++) {
        int l = rand() % n + 1;
        int r = rand() % n + 1;
        if (l > r) swap(l,r);
        int t = rand() % 2 + 1;
        if (t == 1) {
            printf("1 %d %d\n",l,r);
        }
        else {
            int x = rand() % 1000000 + 1;
            printf("2 %d %d %d\n",l,r,x);
        }
    }

    return 0;
}

