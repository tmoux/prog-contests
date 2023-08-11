#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        if (n < 10) {
            cout << "0 0 0\n";
            continue;
        }
        int first_silver = -1;
        int first_bronze = -1;
        int first_unaward = -1;
        int g, s, b;
        for (int i = 0; i < n; i++) {
            if (p[i] != p[0]) {
                first_silver = i;
                break;
            }
        }
        if (first_silver == -1) {
            cout << "0 0 0\n";
            continue;
        }
        for (int i = 2*first_silver+1; i < n; i++) {
            if (p[i] != p[i-1]) {
                first_bronze = i;
                break;
            }
        }
        if (first_bronze == -1) {
            cout << "0 0 0\n";
            continue;
        }
        
        for (int i = n/2; i > first_bronze; i--) {
            if (p[i] != p[i-1]) {
                first_unaward = i;
                break;
            }
        }
        if (first_unaward == -1) {
            cout << "0 0 0\n";
            continue;
        }
        g = first_silver;
        s = first_bronze - first_silver;
        b = first_unaward - first_bronze;
        //printf("%d %d %d\n",g,s,b);
        if (g > 0 && s > 0 && b > 0 && g < s && g < b && (g+s+b) <= n/2) {
            cout << g << ' ' << s << ' ' << b << '\n';
            continue;
        }
        else {
            cout << "0 0 0\n";
            continue;
        }
    }
}

