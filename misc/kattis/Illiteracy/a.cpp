#include <bits/stdc++.h>
using namespace std;
using ll = long long;

char rotate(char c) {
    if (c == 'F') return 'A';
    return c+1;
}

int hsh(const string& s) {
    int res = 0;
    int mult = 1;
    for (int i = 0; i < s.size(); i++) {
        res += (s[i]-'A')*mult;
        mult *= 6;
    }
    return res;
}

int dist[20000000];

string get(string s, int i) {
    char c = s[i];
    if (c == 'A') {
        if (i-1 >= 0) s[i-1] = rotate(s[i-1]);
        if (i+1 < s.size()) s[i+1] = rotate(s[i+1]);
    }
    else if (c == 'B') {
        if (i+1 < s.size() && i-1 >= 0) {
            s[i+1] = s[i-1];
        }
    }
    else if (c == 'C') {
        s[7-i] = rotate(s[7-i]);
    }
    else if (c == 'D') {
        if (i < 7-i) {
            for (int j = 0; j < i; j++) {
                s[j] = rotate(s[j]);
            }
        }
        else {
            for (int j = i+1; j < s.size(); j++) {
                s[j] = rotate(s[j]);
            }
        }
    }
    else if (c == 'E') {
        int y = min(i,7-i);
        s[i-y] = rotate(s[i-y]);
        s[i+y] = rotate(s[i+y]);
    }
    else if (c == 'F') {
        int x = i + 1;
        if (x % 2 == 1) x = (x+9)/2;
        else x /= 2;
        x--;
        assert(0 <= x && x < s.size());
        s[x] = rotate(s[x]);
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dist,-1,sizeof dist);
    string s, t;
    cin >> s >> t;
    dist[hsh(s)] = 0;
    queue<string> q;
    q.push(s);
    while (!q.empty()) {
        string f = q.front(); q.pop();
        int d = dist[hsh(f)];
        //cerr << f << endl;
        if (f == t) {
            cout << d << endl;
            return 0;
        }
        for (int i = 0; i < f.size(); i++) {
            string g = get(f,i);
            /*
            assert(g.size() == 8);
            for (char c: g) {
                if (!('A' <= c && c <= 'F')) {
                    cout << g << endl;
                    cout << f << ' ' << i << endl;
                    exit(0);
                }
            }
            */
            int h = hsh(g);
            if (dist[h] == -1) {
                dist[h] = d + 1;
                q.push(g);
            }
        }
    }
}

