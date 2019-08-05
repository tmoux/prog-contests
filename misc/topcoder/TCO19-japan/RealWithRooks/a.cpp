#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

class RealWithRooks
{
public:
    char which(int x, int y) {
        return ((x+y) % 2 == 0) ? 'W' : 'B';
    }
    bool valid(int R, int C, int x, int y) {
        return 0 <= x && x < R && 0 <= y && y < C;
    }
    vector<string> construct(int R, int C, int N) {
        vector<string> ans;
        for (int i = 0; i < R; i++) {
            string s;
            for (int j = 0; j < C; j++) {
                s += '.';
            }
            ans.push_back(s);
        }
        for (int i = 1; i <= max(R,C) && N > 0; i++) {
            for (int r = 0; r < R && N > 0; r++) {
                for (int c = 0; c < C && N > 0; c++) {
                    if (max(r,c) == i-1) {
                        if (ans[r][c] == '.') {
                            ans[r][c] = which(r,c);
                            N--;
                        }
                    }
                }
            }
        }
        return ans;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    RealWithRooks test;
    auto p = test.construct(4,2,8);
    for (auto s: p) {
        cout << s << '\n';
    }

}

