#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int N, U;
	cin >> N >> U;
	vector<int> energy(N);
	for (int i = 0; i < N; i++) {
		int ai; cin >> ai;
		energy[i] = ai;
	}
	double maxRatio = -1;
	for (int i = 0; i < N-2; i++) {
		int ei = energy[i];
		auto jIT = upper_bound(energy.begin(),energy.end(),ei);
		auto kIT = lower_bound(energy.begin(),energy.end(),ei+U+1);
		kIT--;
		if (jIT != kIT && *jIT <= ei+U && kIT != energy.end() && ei < *jIT && *jIT < *kIT) {
			int ej = *jIT;
			int ek = *kIT;
			double ratio = (double)(ek-ej)/(double)(ek-ei);
			maxRatio = max(maxRatio,ratio);
			if (ratio == maxRatio) {
				//cout << ei << ' ' << ej << ' ' << ek << ' ' << ratio << '\n';
			}
		}
	}
	if (maxRatio == -1) {
		cout << "-1\n";
	}
	else {
		cout << fixed << setprecision(10) << maxRatio << '\n';
	}
	
	
	
	return 0;
}

