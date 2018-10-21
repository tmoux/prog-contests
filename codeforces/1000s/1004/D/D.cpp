#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;

const int maxt = 1000005;
int t, A[maxt];
int M, x;

bool tryGrid(int r, int c) {
    vector<int> check(maxt,0);
    int sourcey = c - x;
    int sourcex = M - sourcey;
    
    //cout << r << ' ' << c << ' ' << sourcex << ' ' << sourcey << '\n';
    if (sourcex < 0 || sourcex >= r || sourcey < 0 || sourcey >= c) return false;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int val = abs(sourcex - i) + abs(sourcey - j);
            if (val > M) return false;
            check[val]++;
        }
    }

    for (int i = 0; i <= M; i++) {
        if (check[i] != A[i]) return false;
    }
    cout << r << ' ' << c << '\n';
    cout << sourcex+1 << ' ' << sourcey+1 << '\n';
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> t;
    for (int i = 0; i < t; i++) {
        int a; cin >> a;
        A[a]++;
        M = max(M,a);
    }
    //check valid
    if (A[0] != 1 || A[1] > 4) {
        cout << -1 << '\n';
        return 0;
    }
    if (t == 1 && A[0] == 1) {
        cout << "1 1\n1 1\n";
        return 0;
    }
    //calculate x
    x = 0;
    for (int i = 1; i <= M; i++) {
        if (A[i] != (i) * 4) {
            x = i;
            break;
        }
    }
    //Now we know the source is at (x, M - x)
    for (int b = 1; b*b <= t; b++) {
        if (t % b == 0) {
            int r = b;
            int c = t / r;
            for (int a = 0; a < 2; a++) {
                if (tryGrid(r,c)) return 0;
                swap(r,c);
            }
        }
    }
    cout << -1 << '\n';
    
    
    return 0;
}
	

