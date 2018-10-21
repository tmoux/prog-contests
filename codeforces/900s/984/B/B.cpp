#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int field[maxn][maxn];
int n, m;

bool check(int i, int j) {
    int dx[] = {-1,0,1};
    int c = 0;
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            if (!(a == b && a == 1)) {
                int ii = i + dx[a];
                int jj = j + dx[b];
                if (ii >= 0 && ii < n && 0 <= jj && jj < m) {
                    if (field[ii][jj] == -1) c++;
                }
            }
        }
    }
    return c == field[i][j];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '*') field[i][j] = -1;
            else if (s[j] == '.') field[i][j] = 0;
            else field[i][j] = s[j] - '0';
        }
    }
    //
    bool isValid = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] >= 0 && !check(i,j)) {
                isValid = false;
                break;
            }
        }
    }

    cout << (isValid ? "YES" : "NO") << '\n';

    return 0;
}
	

