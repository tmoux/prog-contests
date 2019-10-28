#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5+5;
char grid[10][N];
int n;
bool poss[10][N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    poss[9][0] = true;
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < 10; i++) {
            if (grid[i][j] == 'X') continue;
            poss[i][j] |= poss[max(0,i-1)][j-1];
            poss[i][j] |= poss[min(9,i+1)][j-1];
        }
    }
    for (int j = n-2; j >= 0; j--) {
        for (int i = 0; i < 10; i++) {
            if (grid[i][j] == 'X') continue;
            bool p = false;
            p |= poss[max(0,i-1)][j+1];
            p |= poss[min(9,i+1)][j+1];
            poss[i][j] &= p;
        }
    }
    /*
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < n; j++) {
            cout << poss[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    vector<int> pos(n,0);
    pos[0] = 9;
    for (int j = 1; j < n; j++) {
        int pr = pos[j-1];
        if (poss[min(9,pr+1)][j]) 
            pos[j] = min(9,pr+1);
        else if (poss[max(0,pr-1)][j])
            pos[j] = max(0,pr-1);
        else assert(false);
        //cout << j << ": " << pos[j] << endl;
    }
    vector<pair<int,int>> ans;
    pair<int,int> curr = {-1,-1};
    for (int j = 0; j < n-1; j++) {
        if (pos[j+1] == pos[j] - 1 || pos[j] == 0 && pos[j+1] == 0) {
            if (curr.first == -1) {
                curr = {j,1};
            }
            else {
                curr.second++;
            }
        }
        else {
            if (curr.first != -1) {
                ans.push_back(curr);
            }
            curr = {-1,-1};
        }
    }
    if (curr.first != -1) {
        ans.push_back(curr);
    }
    //output
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }
}

