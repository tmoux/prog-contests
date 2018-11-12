#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    const int maxn = 200;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < maxn; j++) {
            cout << (char)((rand() % 26) + 'a');
        }
        cout << '\n';
    }

    return 0;
}

