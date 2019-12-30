#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
int p[maxn];

int in[maxn], out[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        if (p[i] != 0) {
            out[i]++;
            in[p[i]]++;
        }
    }
    vector<int> start, end, iso;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0 && out[i] == 0) {
            iso.push_back(i);
        }
        else if (in[i] == 0) {
            start.push_back(i);
        }
        else if (out[i] == 0) {
            end.push_back(i);
        }
    }
    /*
    for (int i: start) {
        cout << i << ' ';
    }
    cout << '\n';
    for (int i: end) {
        cout << i << ' ';
    }
    cout << '\n';
    for (int i: iso) {
        cout << i << ' ';
    }
    cout << '\n';
    */
    assert(start.size() == end.size());
    if (start.empty()) {
        for (int i = 0; i < iso.size(); i++) {
            //cout << i << ": " << iso[i] << endl;
            p[iso[i]] = iso[(i+1)%iso.size()];
        }
    }
    else {
        for (int i = 0; i < start.size(); i++) {
            if (i == 0) {
                if (!iso.empty()) {
                    p[end[i]] = iso[0];
                    for (int j = 0; j < iso.size(); j++) {
                        if (j < iso.size()-1) {
                            p[iso[j]] = iso[j+1];
                        }
                        else {
                            p[iso[j]] = start[i];
                        }
                    }
                }
                else {
                    p[end[i]] = start[i];
                }
            }
            else {
                p[end[i]] = start[i];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << p[i] << ' ';
    }
    cout << '\n';
}

