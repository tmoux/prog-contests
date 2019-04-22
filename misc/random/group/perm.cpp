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

    Perm<N> inverse() {
        vector<int> r(N+1);
        for (int i = 1; i <= N; i++) {
            r[p[i]] = i;
        }
        return Perm(r);
    }

    bool operator==(const Perm<N>& b) {
        for (int i = 1; i <= N; i++) {
            if (p[i] != b.p[i]) return false;
        }
        return true;
    }

    string pretty() const {
        vector<bool> vis(N+1);
        string res;
        vector<int> currCycle;
        for (int i = 1; i <= N; i++) {
            if (vis[i]) continue;
            if (p[i] == i) continue;
            else {
                int c = i;
                while (!vis[c]) {
                    vis[c] = true;
                    currCycle.push_back(c);
                    c = p[c];
                }
                res += "(";
                for (int j = 0; j < currCycle.size(); j++) {
                    res += to_string(currCycle[j]);
                    if (j < currCycle.size() - 1) res += " ";
                }
                res += ")";
                currCycle.clear();
            }
        }
        if (res.empty()) res = "()";
        return res;
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
    /*
    out << "(";
    for (int i = 1; i <= N; i++) {
        out << c.p[i];
        if (i < N) out << ", ";
    }
    out << ")";
    return out;
    */
    out << c.pretty();
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

    for (auto x: alt) {
        set<Perm<4>> r;
        for (auto g: alt) {
            if (g*x*g.inverse() == x) {
                r.insert(g);
            }
        }
        cout << x << ":\n";
        for (auto g: r) {
            cout << g << ", ";
        }
        cout << '\n';
    }
    /*
    vector<int> per = {0,1,2,3,4};
    vector<Perm<4>> s4;
    do {
        s4.push_back(Perm<4>(per));
        //cout << Perm<5>(per) << '\n';
    } while (next_permutation(per.begin()+1,per.end()));
    
    for (auto g: s4) {
        set<Perm<4>> r;
        for (auto x: s4) {
            r.insert(x*g*x.inverse());
        }
        cout << "element " << g << '\n';
        for (auto p: r) {
            cout << p << ", ";
        }
        cout << "\n";
    }
    */

    return 0;
}

