#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, H; cin >> N >> H;
    vector<pair<char,int>> v1(N), v2(N);
    for (int i = 0; i < N; i++) {
        cin >> v1[i].first >> v1[i].second;
    }
    for (int i = 0; i < N; i++) {
        cin >> v2[i].first >> v2[i].second;
    }
    int h1 = H, h2 = H;
    for (int i = 0; i < N; i++) {
        if (v1[i].first == 'A') {
            if (i == 0 || v2[i-1].first != 'D') 
                h2 -= v1[i].second;
        }
        else {
            if (v2[i].first == 'D') {
                h1 -= v1[i].second;
            }
        }
        if (h1 <= 0) {
            cout << "DEFEAT\n";
            return 0;
        }
        if (h2 <= 0) {
            cout << "VICTORY\n";
            return 0;
        }

        if (v2[i].first == 'A') {
            if (v1[i].first != 'D') {
                h1 -= v2[i].second;
            }
        }
        else {
            if (i == N-1 || v1[i+1].first == 'D') {
                h2 -= v2[i].second;
            }
        }
        if (h1 <= 0) {
            cout << "DEFEAT\n";
            return 0;
        }
        if (h2 <= 0) {
            cout << "VICTORY\n";
            return 0;
        }
    }
    cout << "TIE\n";
}

