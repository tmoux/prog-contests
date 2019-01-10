#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void add(int a, int b) {
    printf("%d %d\n",a,b);
}

int c = 1;

int main()
{
    int k; cin >> k;
    if (!(k&1)) {
        cout << "NO" << '\n';
        return 0;
    }
    if (k == 1) {
        cout << "YES" << '\n';
        cout << "2 1\n1 2\n";
        return 0;
    }
    //k = 3,5,7,...
    cout << "YES\n";
    int nodes = k*k*2 - k + 1;
    int edges = nodes*k/2;
    cout << nodes << ' ' << edges << '\n';
    for (int i = 0; i < k; i++) {
        add(1,++c);
        int root = c;
        vector<int> fi, se;
        for (int i = 0; i < k-1; i++) fi.push_back(++c);
        for (int i = 0; i < k-1; i++) se.push_back(++c);
        for (int i: fi) add(root,i);
        for (int i: fi) {
            for (int j: se) {
                add(i,j);
            }
        }
        for (int i = 0; i < k-1; i += 2) {
            add(se[i],se[i+1]);
        }
    }


    return 0;
}

