#include "Brunolib.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>

long long Bruno(int N, int A[]) {
    std::string ans;
    for (int i = 0; i < N; i += 3) {
        int r = A[i] * 4 + A[i+1] * 2 + A[i+2];
        if (r == 0) continue;
        else if (r == 1) ans += "0";
        else if (r == 2) ans += "1";
        else if (r == 3) ans += "00";
        else if (r == 4) ans += "10";
        else if (r == 5) ans += "11";
        else if (r == 6) ans += "0";
        else if (r == 7) ans += "01";
        /*
        000 : x
        001 : 0
        010 : 1
        011 : 00
        100 : 10
        101 : 11
        110 : 0
        111 : 01
        */
    }
    /*
    std::cerr << "Encoded string: ";
    for (int i = 0; i < N; i++) {
        std::cerr << A[i];
    }
    std::cerr << '\n';
    std::cerr << "Bruno string:   " << ans << '\n';
    */
    long long res = 0;
    long long mult = 1;
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] == '1') res += mult;
        mult *= 2;
    }
    return res;
}
