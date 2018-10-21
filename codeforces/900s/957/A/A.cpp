#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 100;
int N;
int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N;
	string s;
	cin >> s;
	
	char currchar = '?';
	bool isOk = true;
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			currchar = s[i];
		}
		else {
			if (s[i] != '?' && s[i] == currchar) {
				isOk = false;
				break;
			}
			currchar = s[i];
		}
	}
	if (!isOk) {
		cout << "No\n";
		return 0;
	}
	//now check for streaks of 2 or longer
	int currstreak = 0;
	bool hasStreak = false;
	for (int i = 0; i < N; i++) {
		if (s[i] == '?') {
			currstreak++;
		}
		else {
			currstreak = 0;
		}
		if (currstreak >= 2) {
			hasStreak = true;
			break;
		}
	}
	if (hasStreak) {
		cout << "Yes\n";
		return 0;
	}
	
	//now check endpoints
	if (s[0] == '?' || s[N-1] == '?') {
		cout << "Yes\n";
		return 0;
	}
	
	//for 1 and 2-streaks, both endpoints have to have the same color
	bool canBe = false;
	for (int i = 0; i < N; i++) {
		if (s[i] == '?') {
			char leftChar = s[i-1];
			char rightChar = s[i+1];
			//cout << leftChar << ' ' << rightChar << '\n';
			if (leftChar == rightChar) {
				canBe = true;
				break;
			}
		}
	}
	
	if (canBe) {
		cout << "Yes\n";
	}
	else {
		cout << "No\n";
	}
	
	
	return 0;
}

