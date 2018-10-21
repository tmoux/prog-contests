#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            if ((7*i) % 9 == j && j == (8*i-1) % 11) 
                cout << i << ' ' << j << '\n';
        }
    }

    return 0;
}

