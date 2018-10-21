#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << 100 << '\n';
    for (int i = 0; i < 100; i++) {
        cout << 1000 << '\n';
        for (int i = 0; i < 1000; i++) {
            cout << (rand() % 1000 + 1) << ' ';
        }
        cout << '\n';
    }

    return 0;
}

