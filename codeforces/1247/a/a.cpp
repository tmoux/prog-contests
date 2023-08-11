#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int da, db; cin >> da >> db;
    if (da == db) {
        printf("%d0 %d1\n",da,db);
    }
    else if (da == db-1) {
        printf("%d9 %d0\n",da,db);
    }
    else if (da == 9 && db == 1) {
        printf("%d %d0\n",da,db);
    }
    else {
        cout << -1 << '\n';
    }
}

