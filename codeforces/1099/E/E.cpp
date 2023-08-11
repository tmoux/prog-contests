#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int bestans = 2e9+9;
pair<vector<char>,int> best;

vector<char> better(const vector<char>& orig, char X, char Y) {
    int n = orig.size();
    vector<char> t1(n), t2(n);
    for (int i = 0; i < n; i += 2) {
        t1[i] = X;
        t2[i] = Y;
        if (i+1 < n) {
            t1[i+1] = Y;
            t2[i+1] = X;
        }
    }
    int d1 = 0, d2 = 0;
    for (int i = 0; i < n; i++) {
        d1 += t1[i] != orig[i];
        d2 += t2[i] != orig[i];
    }
    return d1 < d2 ? t1 : t2;
}

vector<vector<char>> go(vector<char> perm, const vector<vector<char>>& arr, int flip) {
    int n = arr.size();
    int m = arr[0].size();
    vector<vector<char>> aqq(n,vector<char>(m));
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            aqq[i] = better(arr[i],perm[0],perm[1]);
        }
        else {
            aqq[i] = better(arr[i],perm[2],perm[3]);
        }
    }

    int diff = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            diff += (arr[i][j] != aqq[i][j]);
        }
    }
    //cout << "diff = " << diff << '\n';
    if (diff < bestans) {
        bestans = diff;
        best.first = perm;
        best.second = flip;
    }
    return aqq;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<char>> arr(n,vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    vector<char> perm = {'A','C','G','T'};
    do {
        go(perm,arr,0);
    } while (next_permutation(begin(perm),end(perm)));

    vector<vector<char>> flipped(m,vector<char>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            flipped[i][j] = arr[j][i];    
            //cout << flipped[i][j];
        }
        //cout << '\n';
    }

    perm = {'A','C','G','T'};
    do {
        auto a = go(perm,flipped,1);
        /*
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
        */
    } while (next_permutation(begin(perm),end(perm)));

    //output
    auto table = go(best.first,best.second==0?arr:flipped,best.second);
    //cout << bestans << '\n';
    if (best.second == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << table[i][j];
            }
            cout << '\n';
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << table[j][i];
            }
            cout << '\n';
        }
    }

    return 0;
}

