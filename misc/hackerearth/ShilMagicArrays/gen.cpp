#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    int n; cin >> n;
    printf("%d %d\n",n,n);
    for (int i = 0; i < n; i++) {
        int t = rand() % 2 + 1;
        if (t == 1) {
            int i = rand() % n + 1, k = rand() % n + 1;
            printf("1 %d %d\n",i,k);
        }
        else {
            int k = rand() % n + 1;
            printf("2 %d\n",k);
        }
    }

    return 0;
}

