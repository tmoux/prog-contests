#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    int N, M, Q; cin >> N >> M >> Q;
    printf("%d %d %d\n",N,M,Q);
    for (int i = 0; i < M; i++) {
        int l = rand() % N + 1;
        int r = rand() % N + 1;
        if (l > r) swap(l,r);
        printf("%d %d\n",l,r);
    }
    int tot = 100000;
    while (Q--) {
        int t = rand() % N + 1;
        int y = rand() % (tot);
        tot -= y;    
        cout << t << ' ' << y << ' ';
        for (int i = 0; i < y; i++) {
            int j = rand() % N + 1;
            cout << j << ' ';
        }
        cout << '\n';
    }

    return 0;
}

