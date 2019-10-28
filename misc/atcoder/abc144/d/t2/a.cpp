#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 2; z++) {
                bool op1 = (!(!x || y)) && (!(y&&(y^z)));
                bool op2 = !(y&&(y^z));
                printf("%d %d %d: %d %d\n",x,y,z,op1,op2);
            }
        }
    }
}

