#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class CovidCinema
{
public:
    int R, C;
    vector<string> fill(int x, int y, int A) {
        vector<string> res;
        string r = "";
        for (int j = 0; j < C; j++) r += '.';
        for (int i = 0; i < R; i++) {
            res.push_back(r);
        }
        for (int i = 0; i <= x; i++) {
            for (int j = 0; j <= y; j++) {
                if (A > 0) {
                    res[i][j] = 'A';
                    A--;
                }
            }
        }
        return res;
    }

    vector<string> fill2(int x, int y, int A) {
        vector<string> res;
        string r = "";
        for (int j = 0; j < C; j++) r += '.';
        for (int i = 0; i < R; i++) {
            res.push_back(r);
        }
        for (int j = 0; j <= y; j++) {
            for (int i = 0; i <= x; i++) {
                if (A > 0) {
                    res[i][j] = 'A';
                    A--;
                }
            }
        }
        return res;
    }

    void fillB(vector<string>& grid, int B) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 'A') continue;
                bool poss = true;
                if (i > 0 && grid[i-1][j] == 'A') poss = false;
                if (j > 0 && grid[i][j-1] == 'A') poss = false;
                if (poss && B > 0) {
                    grid[i][j] = 'B';
                    B--;
                }
            }
        }
    }
    bool poss(vector<string>& grid, int A, int B) {
        int ca = 0, cb = 0;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 'A') ca++;
                else if (grid[i][j] == 'B') cb++;
            }
        }
        return ca == A && cb == B;
    }
    void ifswap(int swp, vector<string>& grid) {
        if (!swp) return;
        else {
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (grid[i][j] == 'A') 
                        grid[i][j] = 'B';
                    else if (grid[i][j] == 'B') 
                        grid[i][j] = 'A';
                }
            }
        }
    }
    vector<string> seat(int R_, int C_, int A, int B) {
        R = R_;
        C = C_;
        for (int swp = 0; swp < 2; swp++) {
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    auto grid = fill(i,j,A);
                    fillB(grid,B);
                    /*
                    for (auto s: grid) {
                        cout << s << '\n';
                    }
                    */
                    if (poss(grid,A,B)) {
                        ifswap(swp,grid);
                        return grid;
                    }
                    
                    grid = fill2(i,j,A);
                    fillB(grid,B);
                    /*
                    for (auto s: grid) {
                        cout << s << '\n';
                    }
                    */
                    if (poss(grid,A,B)) {
                        ifswap(swp,grid);
                        return grid;
                    }
                }
            }
            swap(A,B);
        }
        return {};
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int R, C, A, B; cin >> R >> C >> A >> B;
    CovidCinema t;    
    auto ans = t.seat(R,C,A,B);
    cout << "ans : \n";
    for (auto s: ans) {
        cout << s << '\n';
    }
}
