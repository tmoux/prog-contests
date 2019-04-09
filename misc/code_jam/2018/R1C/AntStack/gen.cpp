#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << "100\n";
    for (int i = 0; i < 100; i++) {
        if (i < 6) {
            cout << "100000\n";
            for (int i = 0; i < 100000; i++) {
                int r = rand() % 1000000000 + 1;
                cout << r << ' ';
            }
            cout << '\n';
        }
        else {
            cout << "500\n";
            for (int i = 0; i < 500; i++) {
                int r = rand() % 1000000000 + 1;
                cout << r << ' ';
            }
            cout << '\n';
        }
    }
}

