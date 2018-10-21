#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
typedef long long ll;

int last, n;
vector<int> child[26];
int indegree[26];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    char c;
    cin >> c >> n;
    last = c - 'a';
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 1; i + j < n; j++) {
            int idx = 0;
            while (idx < min(s[i].size(),s[i+j].size()) && s[i][idx] == s[i+j][idx]) {
                idx++;
            }
            if (idx < min(s[i].size(),s[i+j].size())) {
                int a = s[i][idx] - 'a', b = s[i+j][idx] - 'a';
                child[b].push_back(a);
                indegree[a]++;
            }
            if (idx == s[i+j].size() && idx != s[i].size()) {
                //not possible
                cout << 1 << '\n';
                return 0;
            }
        }
    }

    /*
    for (int i = 0; i <= last; i++) {
        cout << i << ": ";
        for (int j: child[i]) {
            cout << j << ' ';
        }
        cout << '\n';
    }
    */
    queue<int> q;
    vector<int> ret;
    for (int i = 0; i <= last; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        if (q.size() > 1) {
            //incomplete
            cout << 0 << '\n';
            return 0;
        }
        int f = q.front();
        ret.push_back(f);
        for (int j: child[f]) {
            indegree[j]--;
            if (indegree[j] == 0) {
                q.push(j);
            }
        }
        q.pop();
    }
    if (ret.size() != last + 1) {
        //not valid
        cout << 1 << '\n';
        return 0;
    }
    //now we know it is valid
    for (int i = ret.size() - 1; i >= 0; i--) {
        cout << (char)(ret[i]+'a');
    }
    cout << '\n';

    return 0;
}
	

