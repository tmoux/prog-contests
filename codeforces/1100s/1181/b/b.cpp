#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef vector<int> num;

num operator+(const num& a, const num& b) {
    int carry = 0;
    num res(a.size());
    if (a.size() < b.size()) return b+a;
    for (int i = 0; i < a.size(); i++) {
        res[i] = carry + a[i] + (b.size() > i ? b[i] : 0);    
        if (res[i] >= 10) {
            res[i] -= 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
    }
    if (carry > 0) {
        res.push_back(carry);
    }
    return res;
}

bool operator<(const num& a, const num& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size()-1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return false;
}

void pr(const num& a) {
    for (int i = a.size()-1; i >= 0; i--) {
        cout << a[i];
    }
    cout << '\n';
}

num v;

num split(int i) {
    num a;
    for (int j = i; j >= 0; j--) {
        a.push_back(v[j]);
    }
    num b;
    for (int j = v.size()-1; j > i; j--) {
        b.push_back(v[j]);
    }
    num res = a + b;
    /*
    cout << "split = " << i << '\n';
    pr(a);
    pr(b);
    pr(res);
    */
    //cout << "\n\n";
    //pr(res);
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int l; cin >> l;
    for (int i = 0; i < l; i++) {
        char c; cin >> c;
        v.push_back(c-'0');
    }
    int mid = (l-1)/2;
    num best = {-1};
    int cnt = 5;
    for (int i = mid; i >= 0 && cnt > 0; i--) {
        if (v[i+1] == 0) continue;
        num tr = split(i);
        cnt--;
        if (best[0] == -1 || tr < best) {
            best = tr;
        }
    }
    cnt = 5;
    for (int i = mid+1; i < v.size() - 1 && cnt > 0; i++) {
        if (v[i+1] == 0) continue;
        num tr = split(i);
        cnt--;
        if (best[0] == -1 || tr < best) {
            best = tr;
        }
        break;
    }
    pr(best);
}


