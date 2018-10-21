#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 50;
int L, W;
struct Car
{
    int O, I, S;
} cars[maxn];
bool blocked[maxn][maxn];
int t = 0;

void paint(int r, int i, int S, bool isLeft) {
    int a = isLeft ? -1 : 1;
    for (int j = 1; j <= S; j++) {
        int off = i+a*j;
        if (0 <= off && off < W) {
            blocked[r][off] = true;
        }
    }
}

void update() {
    memset(blocked,0,sizeof blocked);
    for (int i = 1; i <= L; i++) {
        int O = cars[i].O, S = cars[i].S, I = cars[i].I;
        if (i % 2 == 1) {
            //going right
            int s = O + S*t; 
            for (int a = -100000; a <= 100000; a++) {
                paint(i,s+a*I,S,0);
            }
        }
        else {
            int s = O - S*t;
            for (int a = -100000; a <= 100000; a++) {
                paint(i,s+a*I,S,1);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> L >> W;
    for (int i = 1; i <= L; i++) {
        cin >> cars[i].O >> cars[i].I >> cars[i].S;
    }

    int p; cin >> p;
    int r = L+1, c = p;
    string M; cin >> M;
    for (char chr: M) {
        if (chr == 'U') r--;
        if (chr == 'D') r++;
        if (chr == 'L') c--;
        if (chr == 'R') c++;
        if (r <= 0) {
            cout << "safe\n";
            return 0;
        }
        update();
        t++;
        if (blocked[r][c]) {
            cout << "squish\n";
            return 0;
        }
        /*
        cout << r << ' ' << c << '\n';
        for (int i = 1; i <= L; i++) {
            for (int j = 0; j < W; j++) {
                cout << blocked[i][j] << ' ';
            }
            cout << '\n';
        }
        */
    }
    if (r >= 1) {
        cout << "squish\n";
    }
    else cout << "safe\n";
    return 0;
}

