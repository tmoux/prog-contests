#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<int N>
struct Perm {
    vector<int> p;
    Perm() {}
    Perm(vector<int> _p) {
        p = _p;
    }
    Perm<N> operator*(Perm<N> b) {
        vector<int> r(N+1);
        for (int i = 1; i <= N; i++) {
            r[i] = p[b.p[i]];    
        }
        return Perm(r);
    }

    bool operator==(const Perm<N>& b) {
        for (int i = 1; i <= N; i++) {
            if (p[i] != b.p[i]) return false;
        }
        return true;
    }

    bool operator<(const Perm<N>& b) const {
        for (int i = 1; i <= N; i++) {
            if (p[i] != b.p[i]) return p[i] < b.p[i];
        }
        return false;
    }
};

template<int N>
ostream& operator<<(ostream& out, const Perm<N>& c) {
    out << "(";
    for (int i = 1; i <= N; i++) {
        out << c.p[i];
        if (i < N) out << ", ";
    }
    out << ")";
    return out;
}

int main()
{
    vector<Perm<4>> alt = {Perm<4>({0,1,2,3,4}),
                           Perm<4>({0,1,3,4,2}),
                           Perm<4>({0,1,4,2,3}),
                           Perm<4>({0,2,1,4,3}),
                           Perm<4>({0,2,3,1,4}),
                           Perm<4>({0,2,4,3,1}),
                           Perm<4>({0,3,1,2,4}),
                           Perm<4>({0,3,2,4,1}),
                           Perm<4>({0,3,4,1,2}),
                           Perm<4>({0,4,1,3,2}),
                           Perm<4>({0,4,2,1,3}),
                           Perm<4>({0,4,3,2,1})};

    vector<Perm<4>> H = {Perm<4>({0,1,2,3,4}),
                         Perm<4>({0,2,3,1,4}),
                         Perm<4>({0,3,1,2,4})};
    set<set<Perm<4>>> ans;
    for (auto a: alt) {
        cout << a << ": ";
        set<Perm<4>> s;
        for (auto h : H) {
            for (auto k: H) {
                s.insert(h*(a*k));    
            }
        }
        for (auto b: s) {
            cout << b << " , ";
        }
        cout << "\n\n";
        ans.insert(s);
    }

    cout << "answer:\n";
    for (auto s: ans) {
        for (auto a: s) {
            cout << a << " , ";
        }
        cout << '\n';
    }

    return 0;
}

