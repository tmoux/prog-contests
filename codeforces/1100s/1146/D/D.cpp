#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+10;
int n, q;
int a[maxn], orig[maxn];
int BLOCK;
int bucket[maxn];
bool flip[maxn];
int sett[maxn]; //0 = nothing, 1 = 1, 2 = 0;
int start[maxn];

int get(int x) {
    if (sett[bucket[x]] == 1) return 1;
    if (sett[bucket[x]] == 2) return 0;
    else {
        if (flip[bucket[x]]) return !a[x];
        else return a[x];
    }
}

void REFRESH(int b) {
    if (sett[b] == 1) {
        for (int i = start[b]; bucket[i] == b; i++) {
            a[i] = 1;    
        }
    }
    else if (sett[b] == 2) {
        for (int i = start[b]; bucket[i] == b; i++) {
            a[i] = 0;
        }
    }
    else {
        if (flip[b]) {
            for (int i = start[b]; bucket[i] == b; i++) {
                a[i] = !a[i];
            }
        }
    }
    sett[b] = 0;
    flip[b] = false;
}

void SET(int l, int r, int x) { //x = 1 --> 1, x = 2 --> 0
    assert(l <= r);
    if (bucket[l] == bucket[r]) {
        REFRESH(bucket[l]);
        for (; l <= r; l++) {
            a[l] = x == 1 ? 1 : 0;
        }
        return;
    }
    //set [l,r] to x
    if (l != start[bucket[l]]) {
        //do it manually
        REFRESH(bucket[l]);
        for (; bucket[l] == bucket[l-1]; l++) {
            a[l] = x == 1 ? 1 : 0;        
        }
    }
    while (bucket[l] < bucket[r]) {
        //cout << l << ' ' << bucket[l] << endl;
        assert(l == start[bucket[l]]);
        sett[bucket[l]] = x;
        flip[bucket[l]] = false;
        l = start[bucket[l] + 1];
        //cout << l << ' ' << bucket[l] << ' ' << r << endl;
    }
    REFRESH(bucket[r]);
    assert(l <= r && bucket[l] == bucket[r]);
    for (; l <= r; l++) {
        a[l] = x == 1 ? 1 : 0;
    }
}

void FLIP(int l, int r) {
    assert(l <= r);
    if (bucket[l] == bucket[r]) {
        REFRESH(bucket[l]);
        for (; l <= r; l++) {
            a[l] = !a[l];
        }
        return;
    }
    if (l != start[bucket[l]]) {
        //do it manually
        REFRESH(bucket[l]);
        for (; bucket[l] == bucket[l-1]; l++) {
            a[l] = !a[l];       
        }
    }
    while (bucket[l] != bucket[r]) {
        assert(l == start[bucket[l]]);
        if (sett[bucket[l]] != 0) {
            sett[bucket[l]] = sett[bucket[l]] == 1 ? 2 : 1;
        }
        else {
            flip[bucket[l]] = true;
        }
        l = start[bucket[l]+1];
    }
    REFRESH(bucket[r]);
    for (; l <= r; l++) {
        a[l] = !a[l];    
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> orig[i];
    BLOCK = sqrt(maxn) + 1;
    int offset = 1e5;    
    for (int i = -1e5; i <= 1e5; i++) {
        bucket[i+offset] = (i+offset)/BLOCK;
        if (i+offset == 0 || bucket[i+offset] != bucket[i+offset-1]) {
            start[bucket[i+offset]] = i + offset;
        }
    }
    /*
    SET(0,5,1);
    FLIP(3,7);
    for (int i = 0; i <= 10; i++) {
        cout << i << ": " << get(i) << '\n';
    }
    */
    while (q--) {
        char c; cin >> c;
        int x; cin >> x;
        cout << c << ' ' << x << endl;
        if (c == '<') {
            if (x == 0) {
                SET(0,x+offset-1,1);
                SET(x+offset+1,2e5,2);
            }
            else if (x > 0) {
                SET(0,x+offset-1,1);
                FLIP(1e5-abs(x)+1,1e5+abs(x)-1);
                SET(x+offset+1,2e5,2);
            }
            else {
                SET(0,x+offset-1,1);
                SET(x+offset+1,2e5,2);
            }
        }
        else {
            if (x == 0) {
                SET(0,x+offset-1,2);
                SET(x+offset+1,2e5,1);
            }
            else if (x > 0) {
                SET(x+offset+1,2e5,1);
                SET(0,x+offset-1,2);
            }
            else {
                SET(0,x+offset-1,2);
                FLIP(1e5-abs(x)+1,1e5+abs(x)-1);
                SET(x+offset+1,2e5,1);
            }
        }
        for (int i = -5; i <= 5; i++) {
            cout << get(i+offset) << ' ';
        }
        cout << '\n';
    }
    for (int i = 1; i <= n; i++) {
        cout << (get(orig[i]+offset)==0?orig[i]:-orig[i]) << ' ';
    }
    cout << '\n';
}

