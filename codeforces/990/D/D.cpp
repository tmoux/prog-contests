#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, a, b;
bool mat[maxn][maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a >> b;
    if (min(a,b) == 1 && (n > 3 || a != b || n == 1)) {
        //possible
        cout << "YES\n";
        if (a == b) {
            for (int i = 0; i < n - 1; i++) {
                mat[i][i+1] = 1;
                mat[i+1][i] = 1;
            }
        }
        else if (a == 1) {
            //b-1 vertices connected to everyone else
            for (int i = 0; i < b-1; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        mat[i][j] = 1;
                        mat[j][i] = 1;
                    }
                }
            }
        }
        else {
            //b = 1, so a - 1 vertices not connected to anything, and n-(a-1) vertices complete graph
            for (int i = 0; i < n - (a-1); i++) {
                for (int j = 0; j < n - (a-1); j++) {
                    if (i != j) {
                        mat[i][j] = 1;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << mat[i][j];
            }
            cout << '\n';
        }
    }
    else {
        cout << "NO\n";
    }


    return 0;
}
	

