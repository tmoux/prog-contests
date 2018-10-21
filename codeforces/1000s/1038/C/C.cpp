#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    ll A = 0, B = 0;
    cin >> n;
    priority_queue<int> va, vb;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        va.push(ai);
    }
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        vb.push(ai);
    }
    for (int i = 0; i < 2*n; i++) {
        priority_queue<int>* mine, *other;
        ll* my_score, *other_score;
        if (i % 2 == 0) {
            mine = &va, other = &vb;
            my_score = &A, other_score = &B;
        }
        else {
            mine = &vb, other = &va;
            my_score = &B, other_score = &A;
        }

        if (mine->empty()) {
            int x = other->top();
            other->pop();
        }
        else if (other->empty()) {
            int x = mine->top();
            mine->pop();
            *my_score += x;
        }
        else {
            int x = mine->top(), y = other->top();
            if (x >= y) {
                *my_score += x;
                mine->pop();
            }
            else {
                other->pop();
            }
        }
        //cout << A << ' ' << B << '\n';
    }
    cout << A-B << '\n';

    return 0;
}

