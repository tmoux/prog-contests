#include "grader.h"
#include <algorithm>
using namespace std;
// If you find it necessary, you may import standard libraries here.

void helpBessie(int ID)
{
	//give up if N is larger than 5500
	int N = getTrainLength();
	int K = getWindowLength();
	int i = getCurrentCarIndex();
	int currPass = getCurrentPassIndex();
	if (N <= 5500 && currPass == 0) {
		set(i, -1*ID-1);
		if (i + 1 >= K) {
			int minNum = 2000000000;
			for (int j = i-K+1; j <= i; j++) {
				minNum = min(minNum,(get(j)+1)*-1);
			}
			shoutMinimum(minNum);
		}
	}
}