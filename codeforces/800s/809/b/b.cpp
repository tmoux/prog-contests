#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool ask(int x, int y) {
    if (x == -1) return false;
    printf("1 %d %d\n",x,y);
    fflush(stdout);
    string s; cin >> s;
    return s == "TAK";
}

void answer(int x, int y) {
    printf("2 %d %d\n",x,y);
    fflush(stdout);
    exit(0);
}

int n, k;

int get(int l, int r) {
    if (l > r) return -1;
    while (l < r) {
        int m = (l+r)/2;
        if (ask(m,m+1)) {
            r = m;
        }
        else l = m+1;
    }
    return l;
}

int main() {
    cin >> n >> k;
    int x = get(1,n);
    int y = get(1,x-1);
    if (!ask(y,x)) y = get(x+1,n);
    answer(x,y);
}

