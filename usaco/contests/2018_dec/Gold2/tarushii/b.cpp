#include <bits/stdc++.h>
using namespace std;
struct subset {
	int s[5];
	subset () {
		for (int i = 0; i < 5; i++) s[i] = 0;
	}
	bool operator<(const subset& a) const{
		for (int i = 0; i < 5; i++){
			if (s[i] < a.s[i]) return true;
			if (s[i] > a.s[i]) return false;
		}
		return false;
	}
};
int N;
const int MXN = 5e4+10;
vector<int> fav[MXN];
map<subset, int> c;

int main(){
	ifstream cin("cowpatibility.in");
	ofstream cout("cowpatibility.out");
	cin >> N;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < 5; j++){
			int x; cin >> x;
			fav[i].push_back(x);
		}
		sort(fav[i].begin(), fav[i].end());
	}
	long long compat = 0;
	subset v = subset();
	for (int i = 0; i < N; i++){
		for (int j = 1; j < (1 << 5); j++){
			int x = 0;
			for (int k = 0; k < 5; k++){
				if (j&(1<<k)){
					v.s[x++] = fav[i][k];
				}
			}
			for (int k = x; k < 5; k++) v.s[k] = 0;
      //compat += c[v]*((x&1)?1:-1);
			if (x%2) {
				compat = compat+c[v];
			}
			else compat-=c[v];
			c[v]++;
		}
	/*
		int c1 = 0;
		int c2 = 0;
		int c3 = 0;
		
		for (int j = 0; j < 5; j++){
			subset v = subset();
			v.s[0] = fav[i][j];
			c1+=c[v];
			c[v]++;
			for (int k = j+1; k < 5; k++){
				subset v = subset();
				v.s[0] = fav[i][j]; v.s[1] = fav[i][k]; v.s[2] = 0;
				c2+=c[v];
				c[v]++;
				int x = 0;
				for (int l = 0; l < 5; l++){
					if (l!=j && l!=k){
						v.s[x++] = fav[i][l];
					}
				}
				c3+=c[v];
				c[v]++;
			}
		}
		int c4 = 0;
		for (int j =0 ; j < 5; j++){
			subset v = subset();
			int x = 0;
			for (int k = 0; k < 5; k++){
				if (k!=j) v.s[x++] = fav[i][k];
			}
			c4+=c[v];
			c[v]++;
		}
		subset v = subset();
		for (int j = 0; j < 5; j++) v.s[j] = fav[i][j];
		int c5= c[v];
		c[v]++;*/
		//compat= compat+ (c1-c2+c3-c4+c5);
		//cout << compat << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4 << ' ' << c5 <<  endl;
	}
	long long ans = ((long long)N*(N-1))/2 - compat;
	cout << ans;
}
