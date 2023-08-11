#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string a = "abc";
    for (int i = 0; i < 1000000; i++) {
        cout << (a[i%3]);
    }
    cout << '\n';
}

