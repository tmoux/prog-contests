#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;

pair<string,int> history[2000];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    unordered_map<string,pair<int,int>> score;
    for (int i = 0; i < n; i++) {
        string s; int d;
        cin >> s >> d;
        score[s] = {i,score[s].second+d};
        history[i] = {s,d};
    }
    vector<string> winners;
    int maxscore = -2000000000;
    for (auto p: score) {
        if (p.second.second > maxscore) {
            maxscore = p.second.second;
            winners = {p.first};
        }
        else if (p.second.second == maxscore) {
            winners.push_back(p.first);
        }
    }
    

    unordered_map<string,int> sc;
    for (int i = 0; i < n; i++) {
        sc[history[i].first] += history[i].second;
        if (find(winners.begin(),winners.end(),history[i].first) != winners.end() && sc[history[i].first] >= maxscore) {
            cout << history[i].first << '\n';
            return 0;

        }
    }

    return 0;
}
	

