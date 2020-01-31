#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;

struct Card
{
    char rank, suit;
};

Card grid[20][20];

bool good(int i, int j) {
    vector<char> suits;
    set<char> ranks;
    for (int x = i-1; x <= i+1; x++) {
        for (int y = j-1; y <= j+1; y++) {
            suits.push_back(grid[x][y].suit);
            ranks.insert(grid[x][y].rank);
        }
    }
    sort(suits.begin(),suits.end());
    return (suits.front() == suits.back()) || ranks.size() == 9;
}

int dist(pair<int,int> a, pair<int,int> b) {
    return max(abs(a.first-b.first),abs(a.second-b.second));
}

vector<pair<int,int>> ans;
bool check() {
    ans.clear();
    vector<pair<int,int>> vs;
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-1; j++) {
            if (good(i,j)) {
                vs.push_back({i,j});
            }
        }
    }
    for (int i = 0; i < vs.size(); i++) {
        for (int j = i+1; j < vs.size(); j++) {
            if (dist(vs[i],vs[j]) >= 3) {
                ans.push_back(vs[i]);
                ans.push_back(vs[j]);
                return true;
            }
        }
    }
    return false;
}

void output() {
    printf("Put the first square to (%d, %d).\n",ans[0].first,ans[0].second);
    printf("Put the second square to (%d, %d).\n",ans[1].first,ans[1].second);
    exit(0);
}

int main() {
    cin >> n >> m;
    vector<pair<pair<int,int>,char>> jokers;
    set<pair<char,char>> cards;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            string s; cin >> s;
            grid[i][j] = {s[0],s[1]};
            cards.insert({s[0],s[1]});
            if (grid[i][j].rank == 'J' && (s[1] == '1' || s[1] == '2')) {
                jokers.push_back({{i,j},s[1]});
            }
        }
    }
    vector<Card> v;
    for (char r: {'2','3','4','5','6','7','8','9','T','J','Q','K','A'}) {
        for (char s: {'C','D','H','S'}) {
            if (!cards.count({r,s})) {
                v.push_back({r,s});
            }
        }
    }
    if (jokers.size() == 0) {
        if (check()) {
            printf("Solution exists.\n");
            printf("There are no jokers.\n");
            output();
        }
    }
    else if (jokers.size() == 1) {
        auto p = jokers[0].first;
        for (Card c: v) {
            grid[p.first][p.second] = c;
            if (check()) {
                printf("Solution exists.\n");
                printf("Replace J%c with %c%c.\n",jokers[0].second,c.rank,c.suit);
                output();
            }
        }
    }
    else {
        assert(jokers.size() == 2);
        auto p1 = jokers[0].first;
        auto p2 = jokers[1].first;
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size(); j++) {
                if (i == j) continue;
                grid[p1.first][p1.second] = v[i];
                grid[p2.first][p2.second] = v[j];
                if (check()) {
                    printf("Solution exists.\n");
                    if (jokers[0].second == '1') 
                        printf("Replace J1 with %c%c and J2 with %c%c.\n",v[i].rank,v[i].suit,v[j].rank,v[j].suit);
                    else
                        printf("Replace J1 with %c%c and J2 with %c%c.\n",v[j].rank,v[j].suit,v[i].rank,v[i].suit);
                    output();
                }
            }
        }
    }
    printf("No solution.\n");
}

