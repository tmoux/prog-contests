#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << "20\n";
    for (int i = 0; i < 20; i++) {
        string s;
        for (int j = 0; j < 50000; j++) {
            char c = (char)(rand() % 40) + 'A';
            s += c;
        }
        cout << s << '\n';
    }

    return 0;
}

