/*
ID: silxikys
PROG: rockers
LANG: C
*/

//this is the solution given in the analysis, not mine

#include <stdio.h>
#define MAX 25

int dp[MAX][MAX][MAX], length[MAX];

int 
main ()
{
    FILE   *in = fopen ("rockers.in", "r");
    FILE   *out = fopen ("rockers.out", "w");
    int     a, b, c, d, best, numsongs, cdlength, numcds;
    fscanf (in, "%d%d%d", &numsongs, &cdlength, &numcds);
    for (a = 1; a <= numsongs; a++)
	fscanf (in, "%d", &length[a]);
    best = 0;
    for (a = 0; a < numcds; a++)/* current cd */
	for (b = 0; b <= cdlength; b++)	/* number of minutes used */
	    for (c = 0; c <= numsongs; c++) {	/* last song */
		for (d = c + 1; d <= numsongs; d++) {	/* new song */
		    if (b + length[d] <= cdlength) {
			if (dp[a][b][c] + 1 > dp[a][b + length[d]][d])
			    dp[a][b + length[d]][d] = dp[a][b][c] + 1;
		    }
		    else {
			if (dp[a][b][c] + 1 > dp[a + 1][length[d]][d])
			    dp[a + 1][length[d]][d] = dp[a][b][c] + 1;
		    }
		}
		if (dp[a][b][c] > best)
		    best = dp[a][b][c];
	    }
    fprintf (out, "%d\n", best);
    return 0;
}