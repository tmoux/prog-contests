
#include <iostream>
using namespace std;

#define endl "\n";

int main() {

	int N, t = 1;
	while(true) {
		cin >> N;
		if( N == 0 ) break;
		string elem[N];
		string s;
		for(int i=0;i<N;i++)
			cin >> elem[i];
		getline(cin, s);
		getline(cin, s);
		

		// initialize array to represent whether we can build a string up to length i
		// 0 = no, 1 = yes;
		int memo[s.length()+1];
		fill(memo, memo+s.length()+1, 0);
		memo[0] = 1;

		// loop through all indexes in string S
		for( int i = 1 ; i <= s.length(); i++) {
			// if index is a space character, continue through
			if( memo[i-1] == 1 && s[i-1] == ' ' ){
				memo[i] = 1;
				continue;
			}
			// if we couldn't build a string up to the previous index, we cannot build off of it.
			if( memo[i-1] == 0 ) continue;
			
			// go through all elements
			for(int j = 0; j < N ; j++ ){
				int valid = 1;
				// see if elemental word j is a substring starting at index i of string S
				for(int k = 0 ; k < elem[j].length(); k++){
					if(k+i-1>=s.length() || elem[j][k] != s[k+i-1]){
						valid = 0;
						break;
					}
				}
				// if still valid, then mark index as reachable
				if( valid == 1 ) memo[i+elem[j].length()-1] = 1;
			}
		}
		cout << "Phrase #" << (t++) << ": " << ((memo[s.length()]==1)?"Elemental":"Not Elemental");
		cout << endl;
		cout << endl;
	}	
	return 0;
}
