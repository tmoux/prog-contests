#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    bool vert = false;
    int horiz = 3;
    for (char c: s) {
        if (c == '0') {
            //vertical
            if (!vert) {
                cout << "1 1\n";    
            }
            else {
                cout << "3 1\n";    
            }
            vert = !vert;
        }
        else {
            //horizontal
            horiz = (horiz + 1) % 4;
            cout << (horiz + 1) << ' ' << 3 << '\n';
        }
    }
        

    return 0;
}

