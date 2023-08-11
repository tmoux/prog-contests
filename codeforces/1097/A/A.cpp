#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

char r, s;
bool poss(char rank, char suit) {
    return rank == r || suit == s;    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> r >> s;
    for (int i = 0; i < 5; i++) {
        char rr, ss; cin >> rr >> ss;
        //cout << rr << ' ' << ss << '\n';
        if (poss(rr,ss)) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";

    return 0;
}

