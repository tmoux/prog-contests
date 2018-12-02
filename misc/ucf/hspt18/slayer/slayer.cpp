#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int q, n, m, monsterHealth, monsterAttack;
const int maxn = 105;
const int INF = 1e9+7;

struct Move
{
    int amt, energy;
};

void amax(int& a, int b) {
    a = max(a,b);
}
void amin(int& a, int b) {
    a = min(a,b);
}

int main()
{
    int t; cin >> t;
    for (int a = 1; a <= t; a++) {
        cin >> q >> n >> m >> monsterHealth >> monsterAttack;
        vector<Move> block, charge, attack;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            int y, z; cin >> y >> z;
            (x==1?attack:x==2?block:charge).push_back({y,z});
        }
        //first try all blocks
        int bl[maxn][maxn];
        memset(bl,0,sizeof bl);
        int chargeDmg = 0;
        for (int i = 0; i < charge.size(); i++) {
            Move mo = charge[i];
            for (int j = 0; j <= m; j++) {
                if (i > 0) { 
                    amax(bl[i][j],bl[i-1][j]);
                    if (j-mo.energy >= 0) {
                        amax(bl[i][j],bl[max(0,i-1)][j-mo.energy]+mo.amt);
                    }
                }
                else {
                    if (j-mo.energy >= 0) {
                        amax(bl[i][j],mo.amt);
                    }
                }
                amax(chargeDmg,bl[i][j]);
                //cout << i << ' ' << j << ": " << bl[i][j] << '\n';
            }
        }
        //cout << chargeDmg << '\n';
        if (chargeDmg >= monsterHealth) {
            printf("Fight #%d: Win\n",a);
            continue;
        }
        else {
            int diff = monsterAttack - q + 1;
            int blockCost = INF;
            //cout << diff << '\n';
            if (diff <= 0) {
                blockCost = 0;
            }
            else {
                int bl[maxn][maxn];
                memset(bl,0,sizeof bl);
                for (int i = 0; i < block.size(); i++) {
                    Move mo = block[i];
                    for (int j = 0; j <= m; j++) {
                        if (i > 0) {
                            amax(bl[i][j],bl[i-1][j]);
                            if (j-mo.energy >= 0) {
                                amax(bl[i][j],bl[max(0,i-1)][j-mo.energy]+mo.amt);
                            }
                        }
                        else {
                            if (j-mo.energy >= 0) {
                                amax(bl[i][j],mo.amt);
                            }
                        }
                        if (bl[i][j] >= diff) {
                            amin(blockCost,j);
                        }
                    }
                }
            }
            //cout << blockCost << '\n';
            if (blockCost == INF) {
                //impossible
                printf("Fight #%d: Lose\n",a);
                continue;
            }
            else {
                m -= blockCost;
                //cout << m << '\n';
                int cr[2*maxn][maxn];
                memset(cr,0,sizeof cr);
                charge.insert(charge.end(),attack.begin(),attack.end());
                int maxDmg = 0;
                for (int i = 0; i < charge.size(); i++) {
                    Move mo = charge[i];
                    for (int j = 0; j <= m; j++) {
                        if (i > 0) {
                            amax(cr[i][j],cr[i-1][j]);
                            if (j-mo.energy >= 0) {
                                amax(cr[i][j],cr[max(0,i-1)][j-mo.energy]+mo.amt);
                            }
                        }
                        else {
                            if (j-mo.energy >= 0) {
                                amax(cr[i][j],mo.amt);
                            }
                        }
                        amax(maxDmg,cr[i][j]);
                        //cout << i << ' ' << j << ": " << cr[i][j] << '\n';
                    }
                }
                //cout << maxDmg << '\n';
                if (maxDmg >= monsterHealth) {
                    printf("Fight #%d: Win\n",a);
                }
                else {
                    printf("Fight #%d: Lose\n",a);
                }
            }
        }
    }

    return 0;
}

