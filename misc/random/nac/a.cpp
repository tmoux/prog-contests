#include <bits/stdc++.h>
using namespace std;
using ll = long long;

long double getWinProbability(long double ra, long double rb) {
    return 1.0 / (1.0 + pow((long double) 10.0, (rb - ra) / 400.0));
}

long double aggregateRatings(vector<long double> teamRatings)
{
    long double left = 1;
    long double right = 1E4;

    for (int tt = 0; tt < 100; tt++) {
        long double r = (left + right) / 2.0;

        long double rWinsProbability = 1.0;
        for(int i = 0; i < teamRatings.size(); i++)
            rWinsProbability *= getWinProbability(r, teamRatings[i]);

        long double rating = log10(1 / (rWinsProbability) - 1) * 400 + r;

        if (rating > r)
            left = r;
        else
            right = r;
    }

    return (left + right) / 2.0;
}

string teams[30];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n = 25;
    map<string,vector<long double>> cur, mx;
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin,s);
        teams[i] = s;
        //cout << teams[i] << '\n';
    }
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < n; i++) {
            long double r; cin >> r;
            cur[teams[i]].push_back(r);
        }
        for (int i = 0; i < n; i++) {
            long double r; cin >> r;
            mx[teams[i]].push_back(r);
        }
    }
    cout << fixed << setprecision(0);
    for (int i = 0; i < n; i++) {
        cout << aggregateRatings(cur[teams[i]]) << '\n';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cout << aggregateRatings(mx[teams[i]]) << '\n';
    }
}

