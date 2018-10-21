#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

bool ask(int r1, int c1, int r2, int c2) {
    cout << "? " << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
    string ans; cin >> ans;
    return ans[0] == 'Y';
}

int main()
{
    cin >> n;
    int x = 1, y = 1;
    string fwd;
    for (int i = 0; i < n - 1; i++) {
        bool isRight = ask(x+1,y,n,n);
        fwd += isRight ? 'D': 'R';
        if (isRight) x++;
        else y++;
    }
    x = n, y = n;
    string bck;
    for (int i = 0; i < n - 1; i++) {
        bool isUp = ask(1,1,x,y-1);
        bck += (isUp ? 'R' : 'D');
        if (isUp) y--;
        else x--;
    }
    
    //output
    reverse(bck.begin(),bck.end());
    cout << "! " << fwd << bck << endl;
    return 0;
}

