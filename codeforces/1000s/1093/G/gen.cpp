#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    cout << "200000 5\n";
    for (int i = 0; i < 200000; i++) {
        for (int k = 0; k < 5; k++) {
            int r = (rand() % 2000000) - 1000000;
            cout << r << ' ';
        }
        cout << '\n';
    }
    cout << "200000\n";
    for (int i = 0; i < 200000; i++) {
        int t = rand() % 2;
        if (t == 1) {
            cout << 1 << ' ';
            cout << (rand() % 200000) + 1 << ' ';
            for (int k = 0; k < 5; k++) {
                int r = (rand() % 2000000) - 1000000;
                cout << r << ' ';
            }
            cout << '\n';
        }
        else {
            int l = (rand() % 200000) + 1;
            int r = (rand() % 200000) + 1;
            if (l > r) swap(l,r);
            printf("%d %d %d\n",2,l,r);
        }
    }

    return 0;
}

