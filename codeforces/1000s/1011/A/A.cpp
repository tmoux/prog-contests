#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<char> cs;
    string s; cin >> s;
    for (char c: s) {
        cs.push_back(c);
    }
    int weight = 0;
    char prev = 0;
    int cnt = 0;
    sort(cs.begin(),cs.end());
    for (char c: cs) {
        if (c - prev >= 2) {
            weight += (c - 'a' + 1);
            prev = c;
            cnt++;
        }
        if (cnt == k) break;
    }

    if (cnt == k) {
        cout << weight << '\n';
    }
    else {
        cout << -1 << '\n';
    }


    return 0;
}
	

