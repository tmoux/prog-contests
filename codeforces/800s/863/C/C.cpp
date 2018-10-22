#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll k;
int a, b;
int A[4][4], B[4][4];
bool seen[4][4];
vector<int> ps;
vector<pair<int,int>> pos;
void play(int x, int y) {
    if (x != y) {
        if ((x == 1 && y == 3) || (x == 2 && y == 1) || (x == 3 && y == 2)) ps.push_back(1);
        else ps.push_back(-1);
    }
    else ps.push_back(0);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> k >> a >> b;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cin >> B[i][j];
        }
    }
    while (true) {
        seen[a][b] = true;
        play(a,b);
        pos.push_back({a,b});
        int na = A[a][b], nb = B[a][b];
        a = na, b = nb;
        if (seen[na][nb]) break;
    }

    ll Alice = 0, Bob = 0;
    int i;
    for (i = 0; i < ps.size(); i++) {
        if (a != pos[i].first || b != pos[i].second) {
            k--;
            if (ps[i] == 1) Alice++;
            else if (ps[i] == -1) Bob++;
            if (!k) break;
        }
        else break;
    }
    //cout << a << ":" << b << '\n';
    //cout << "K= " << k << ", " << Alice << ' ' << Bob << '\n';
    int aa = 0, bb = 0;
    for (int j = i; j < ps.size(); j++) {
        if (ps[j] == 1) aa++;
        else if (ps[j] == -1) bb++;
        //cout << j << '\n';
    }
    int cycle = ps.size() - i;
    ll r = k/cycle;
    Alice += 1LL*aa*r;
    Bob += 1LL*bb*r;
    int rem = k % cycle;
    for (int j = i; j < i + rem; j++) {
        if (ps[j] == 1) Alice++;
        else if (ps[j] == -1) Bob++;
    }
    //output
    cout << Alice << ' ' << Bob << '\n';

    return 0;
}
