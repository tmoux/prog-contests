#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int maxq = 500005;
int S[maxq];
long prefix[maxq];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	long* left = prefix, tracker = prefix; int* right = S;
	int numElements = 2;
	double currmax = -1;
	int Q; cin >> Q;
	for (int i = 0; i < Q; i++) {
		int type; cin >> type;
		switch (type) {
			case 1:
				int n; cin >> n;
				*right = n;
				right++;
				if (left == prefix) {
					*left = n;
				}
				else {
					*left = *(left-1)  + n;
				}
				left++;
				break;
			case 2:
				int maxnum = *(right-1);
				double newmax = (*tracker + maxnum)/(double)(numElements);
				
		}
	}
	
	
	
	return 0;
}
