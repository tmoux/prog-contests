#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int B;

int ask(int i) {
    cout << i << endl;
    char c; cin >> c;
    assert(c != 'N');
    return c-'0';
}

void answer(vector<int> v) {
    for (auto i = 1; i <= B; i++) {
        cout << v[i];
    }
    cout << endl;
    char c; cin >> c;
    assert(c == 'Y');
}

void solve() {
    vector<int> ans(B+1);
    vector<int> v(B+1);
    if (B == 10) {
        for (int i = 1; i <= B; i++) {
            ans[i] = ask(i);
            //cerr << i << ": " << ans[i] << endl;
        }
        answer(ans); 
    }
    else if (B == 20) {
        for (int i = 1; i <= 5; i++) {
            v[i] = ask(i);
        }
        for (int i = 16; i <= 20; i++) {
            v[i] = ask(i);
        }

        for (int i = 6; i <= 10; i++) {
            v[i] = ask(i);
        }
        for (int i = 11; i <= 15; i++) {
            v[i] = ask(i);
        }

        vector<int> u(B+1);
        for (int i = 1; i <= 5; i++) {
            u[i] = ask(i);
        }
        //same
        bool flag = true;
        for (int i = 1; i <= 5; i++) {
            if (v[i] != u[i]) flag = false;
        }
        if (flag) {
            for (int i = 1; i <= 5; i++) {
                ans[i] = v[i];
            }
            for (int i = 16; i <= 20; i++) {
                ans[i] = v[i];
            }
        }
        else {
            flag = true;
            //check flipped
            for (int i = 1; i <= 5; i++) {
                if (v[i] == u[i]) flag = false;
            }
            if (flag) {
                for (int i = 1; i <= 5; i++) {
                    ans[i] = 1-v[i];
                }
                for (int i = 16; i <= 20; i++) {
                    ans[i] = 1-v[i];
                }
            }
            else {
                flag = true;
                for (int i = 1; i <= 5; i++) {
                    if (u[i] != v[20+1-i]) flag = false;
                    if (flag) {
                        for (int i = 1; i <= 5; i++) {
                            ans[i] = v[20+1-i];
                        }
                        for (int i = 16; i <= 20; i++) {
                            ans[i] = v[20+1-i];
                        }
                    }
                    else {
                        for (int i = 1; i <= 5; i++) {
                            ans[i] = 1-v[20+1-i];
                        }
                        for (int i = 16; i <= 20; i++) {
                            ans[i] = 1-v[20+1-i];
                        }
                    }
                }
            }
        }

        for (int i = 6; i <= 10; i++) {
            u[i] = ask(i);
        }
        flag = true;
        for (int i = 6; i <= 10; i++) {
            if (v[i] != u[i]) flag = false;
        }
        if (flag) {
            for (int i = 6; i <= 10; i++) {
                ans[i] = v[i];
            }
            for (int i = 11; i <= 15; i++) {
                ans[i] = v[i];
            }
        }
        else {
            flag = true;
            //check flipped
            for (int i = 6; i <= 10; i++) {
                if (v[i] == u[i]) flag = false;
            }
            if (flag) {
                for (int i = 6; i <= 10; i++) {
                    ans[i] = 1-v[i];
                }
                for (int i = 11; i <= 15; i++) {
                    ans[i] = 1-v[i];
                }
            }
            else {
                flag = true;
                for (int i = 6; i <= 10; i++) {
                    if (u[i] != v[20+1-i]) flag = false;
                    if (flag) {
                        for (int i = 6; i <= 10; i++) {
                            ans[i] = v[20+1-i];
                        }
                        for (int i = 11; i <= 15; i++) {
                            ans[i] = v[20+1-i];
                        }
                    }
                    else {
                        for (int i = 6; i <= 10; i++) {
                            ans[i] = 1-v[20+1-i];
                        }
                        for (int i = 11; i <= 15; i++) {
                            ans[i] = 1-v[20+1-i];
                        }
                    }
                }
            }
        }
        answer(ans);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t >> B;
    while (t--) {
        solve();
    }
}
