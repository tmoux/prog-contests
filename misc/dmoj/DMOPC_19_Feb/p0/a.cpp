#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, c; cin >> n >> c;
    while (n--) {
        string si;
        cin >> si;
        int xi;
        cin >> xi;
        if (xi > c) printf("%s will advance\n",si.c_str());
        else printf("%s will not advance\n",si.c_str());
    }
}

