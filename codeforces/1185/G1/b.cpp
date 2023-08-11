#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    for (int i = 0; i < 1<<25; i++) {
        int a = 0;
        for (int j = 0; j < 25; j++) {
            if (i&(1<<j)) a++;
        }
    }
}

