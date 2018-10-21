#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << "100000 300000 100000\n";
    for (int i = 0; i < 99999; i++) {
        cout << i+1 << ' ' << i+2 << " 1\n";
    }
    for (int i = 0; i < 200001; i++) {
        int t = (rand() % 100000) + 1;
        int r = (rand() % 100000) + 1;
        int w = (rand() % 1000000000) + 1;
        cout << t << ' ' << r << ' ' << w << '\n';
    }
    for (int i = 0; i < 100000; i++) {
        int r = (rand() % 99999) + 2;
        int w = (rand() % 100000) + 1;
        cout << r << ' ' << w << '\n';
    }
    
    return 0;
}

