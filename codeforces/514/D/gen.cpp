#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << 100000 << ' ' << 5 << ' ' << rand() % 1000000000 << '\n';
    for (int i = 0; i < 100000; i++) {
        for (int j = 0; j < 5; j++) {
            cout << rand() % 100000000 << ' ';
        }
        cout << '\n';
    }

    return 0;
}

