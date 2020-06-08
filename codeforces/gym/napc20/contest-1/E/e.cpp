#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4005;
int n;
vector<string> v;

bool is_sub(const string& a, const string& b) {
    int pt = 0;
    for (int i = 0; i < b.size(); i++) {
        while (pt < a.size() && b[i] != a[pt]) pt++;
        if (pt == a.size()) return false;
        else pt++;
    }
    return true;
}

int par[maxn];

vector<string> q1, q2, q3;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        string si; cin >> si;
        v.push_back(si);
        if (!is_sub(s,si)) {
            cout << "impossible\n";
            return 0;
        }
    }
    sort(v.begin(),v.end(),[](auto& a, auto& b) {
            return a.size() > b.size();
            });
    for (int i = 0; i < v.size(); i++) {
        bool a = q1.empty() || is_sub(q1.back(),v[i]);
        bool b = q2.empty() || is_sub(q2.back(),v[i]);
        if (a && !b) {
            q1.push_back(v[i]);
            for (auto p: q3) q2.push_back(p);
            q3.clear();
        }
        else if (!a && b) {
            q2.push_back(v[i]);
            for (auto p: q3) q1.push_back(p);
            q3.clear();
        }
        else if (a && b) {
            if (q3.empty() || is_sub(q3.back(),v[i])) {
                q3.push_back(v[i]);
            }
            else {
                q1.push_back(v[i]);
                for (auto p: q3) q2.push_back(p);
                q3.clear();
            }
        }
        else {
            cout << "impossible\n";
            return 0;
        }
    }
    for (auto p: q3) {
        q1.push_back(p);
    }
    reverse(q1.begin(),q1.end());
    reverse(q2.begin(),q2.end());
    cout << q1.size() << ' ' << q2.size() << '\n';
    for (auto p: q1) {
        cout << p << '\n';
    }
    for (auto p: q2) {
        cout << p << '\n';
    }
}
