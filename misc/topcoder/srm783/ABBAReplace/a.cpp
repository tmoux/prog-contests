#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct ABBAReplace
{
    int countSteps(string Sprefix, int N, int seed, int threshold) {
        int state = seed;
        string S = Sprefix;
        while (S.size() < N) {
            state = (1LL*state*1103515245+12345) % (1<<31);
            if (state < threshold) {
                S += 'A';
            }
            else {
                S += 'B';
            }
        }
        int ans = 0;
        int stops = 0;
        int target = 0;
        int dist = 0;
        for (int i = 0; i < N; i++) {
            if (S[i] == 'B') {
                ans = max(ans,i-target+adj);
                target++;
                dist = 0;
            }
            else dist++;
        }
        /*
        while (true) {
            cout << S << endl;
            int cnt = 0;
            for (int i = 0; i < N-1; i++) {
                if (S[i] == 'A' && S[i+1] == 'B') {
                    swap(S[i],S[i+1]);
                    i++;
                    cnt++;
                }
            }
            if (!cnt) break;
        }
        */
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    auto t = ABBAReplace();
    string Sprefix; cin >> Sprefix;
    int N, seed, threshold;
    cin >> N >> seed >> threshold;
    cout << t.countSteps(Sprefix,N,seed,threshold) << '\n';
}

