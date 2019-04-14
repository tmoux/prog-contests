#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    srand(time(NULL));
    int t = 100;
    cout << t << '\n';
    for (int i = 0; i < t; i++) {
        int N = 1000;
        cout << N << '\n';
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 50; j++) {
                char c = (char)('a'+(rand()%26));
                //char c = 'a';
                cout << c;
            }
            cout << '\n';
        }
    }

}

