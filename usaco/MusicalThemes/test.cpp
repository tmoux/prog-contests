#include <fstream.h>

int     n;
int     note[5000];

int 
main () {
    ifstream filein ("theme.in");
    filein >> n;
    for (int i = 0; i < n; ++i) 
	filein >> note[i];
    filein.close ();

    int     longest = 1;

    for (int i = 1; i < n; ++i) {
	int     length = 1;
	for (int j = n - i - 1 - 1; j >= 0; --j) {
	    if (note[j] - note[j + 1] == note[j + i] - note[j + i + 1]) {
		++length;
		if (length > i) 
		    length = i;
		if (longest < length)
		    longest = length;
	    }
	    else {
		length = 1;
	    }
	}
    }

    ofstream fileout ("theme.out");
    fileout << ((longest >= 5) ? longest : 0) << endl;
    fileout.close ();

    exit (0);
}