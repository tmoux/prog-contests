#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool like(int a, int b) {
    return a <= b && 2*a >= b;
}

int main() {
    int v1, v2, v3, vm; cin >> v1 >> v2 >> v3 >> vm;
    v1 *= 2;
    v2 *= 2;
    v3 = max(v3,2*min(v3,vm));
    if (!like(vm,v1) && !like(vm,v2) && like(vm,v3)) {
        printf("%d\n%d\n%d\n",v1,v2,v3);
    }
    else printf("-1\n");
}

