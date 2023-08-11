#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
string s, t;
int adj[3][3];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cin >> s >> t;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adj[i][j] = 1;
        }
    }
    adj[s[0]-'a'][s[1]-'a'] = 0;
    adj[t[0]-'a'][t[1]-'a'] = 0;
    //if there's a three-cycle, take it
    //otherwise, must be bidirectional, and third has a self-loop
    cout << "YES\n";
    if (adj[0][1] && adj[1][2] && adj[2][0]) {
        string res = "";
        for (int i = 0; i < n; i++) {
            res += "abc";
        }
        cout << res << '\n';
        return 0;
    }
    else if (adj[2][1] && adj[1][0] && adj[0][2]) {
        string res = "";
        for (int i = 0; i < n; i++) {
            res += "cba";
        }
        cout << res << '\n';
        return 0;
    }
    else {
        vector<int> p = {0,1,2};
        do {
            if (adj[p[0]][p[0]] && adj[p[0]][p[1]] &&
                adj[p[1]][p[2]] && adj[p[2]][p[1]]) {
                string res = "";
                for (int i = 0; i < n; i++) {
                    res += (char)(p[0]+'a');
                }
                for (int i = 0; i < n; i++) {
                    res += (char)(p[1]+'a');
                    res += (char)(p[2]+'a');
                }
                cout << res << '\n';
                return 0;
            }
        } while (next_permutation(p.begin(),p.end()));
        p = {0,1,2};
        do {
            if (adj[p[0]][p[1]] && adj[p[1]][p[0]] && 
                adj[p[0]][p[2]] && adj[p[2]][p[2]]) {
                string res = "";
                for (int i = 0; i < n; i++) {
                    res += (char)(p[0]+'a');
                    res += (char)(p[1]+'a');
                }
                for (int i = 0; i < n; i++) {
                    res += (char)(p[2]+'a');
                }
                cout << res << '\n';
                return 0;
            }
        } while (next_permutation(p.begin(),p.end()));
        assert(false);
    }
}

