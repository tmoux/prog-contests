#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ask(int i, int j) {
    cout << "? " << i << ' ' << j << endl;
    int r; cin >> r;
    if (r == 0) exit(0);
    return r;
}

//4, 8, 15, 16, 23, 42
//2*2, 2*2*2, 3*5, 2*2*2*2, 23, 2*3*7

//(2^5,2^7
//gcd(4*8,4*16) = 2^5
//gcd(2^3*2^2,2^3*2^4) = 2^5
//gcd(2^4*2^2,2^4*2^3) = 2^6

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int p1 = ask(1,2);
    int p2 = ask(3,4);
    int p3 = ask(5,1);
    int p4 = ask(5,3);
    vector<int> dr = {4,8,15,16,23,42};
    vector<int> ans(10);
    //23
    if (p1 % 23 == 0) {
        if (p3 % 23 == 0) {
            ans[1] = 23;
        }
        else ans[2] = 23;
    }
    else if (p2 % 23 == 0) {
        if (p4 % 23 == 0) {
            ans[3] = 23;
        }
        else ans[4] = 23;
    }
    else if (__gcd(p3,p4) % 23 == 0) {
        ans[5] = 23;
    }
    else ans[6] = 23;

    //15
    if (p1 % 15 == 0) {
        if (p3 % 15 == 0) {
            ans[1] = 15;
        }
        else ans[2] = 15;
    }
    else if (p2 % 15 == 0) {
        if (p4 % 15 == 0) {
            ans[3] = 15;
        }
        else ans[4] = 15;
    }
    else if (__gcd(p3,p4) % 15 == 0) {
        ans[5] = 15;
    }
    else ans[6] = 15;

    //42
    if (p1 % 42 == 0) {
        if (p3 % 42 == 0) {
            ans[1] = 42;
        }
        else ans[2] = 42;
    }
    else if (p2 % 42 == 0) {
        if (p4 % 42 == 0) {
            ans[3] = 42;
        }
        else ans[4] = 42;
    }
    else if (__gcd(p3,p4) % 42 == 0) {
        ans[5] = 42;
    }
    else ans[6] = 42; 

    for (int aa = 0; aa < 3; aa++) {
        if (ans[1] == 0 && ans[2] != 0) {
            ans[1] = p1/ans[2];
        }
        if (ans[2] == 0 && ans[1] != 0) {
            ans[2] = p1/ans[1];
        }
        if (ans[3] == 0 && ans[4] != 0) {
            ans[3] = p2/ans[4];
        }
        if (ans[4] == 0 && ans[3] != 0) {
            ans[4] = p2/ans[3];
        }
        if (ans[5] == 0 && ans[1] != 0) {
            ans[5] = p3/ans[1];
        }
        else if (ans[5] == 0 && ans[3] != 0) {
            ans[5] = p4/ans[3];
        }
        if (ans[1] == 0 && ans[5] != 0) {
            ans[1] = p3/ans[5];
        }
        if (ans[3] == 0 && ans[5] != 0) {
            ans[3] = p4/ans[5];
        }
    } 
    if (ans[6] == 0) {
        for (auto i: dr) {
            if (find(ans.begin(),ans.end(),i) == ans.end()) {
                ans[6] = i;
                break;
            }
        }
    }

    //output
    cout << "! ";
    for (int i = 1; i <= 6; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}

//15, 23, (4,8), 16, 42

