// Arup Guha
// 7/18/2018
// Alternate Solution to 2018 SI@UCF Final Contest Problem: Byteland Bands Together

import java.util.*;

public class together_arup {
	
	public static int n;
	public static long[] cost;
	public static long[] nump;
	public static long[] cumfreq;
	public static long[][] memo;
	
	public static void main(String[] args) {
		
		// Read in all of the data.
		Scanner stdin = new Scanner(System.in);
		int n = stdin.nextInt();
		nump = new long[n];
		cost = new long[n];
		for (int i=0; i<n; i++)	nump[i] = stdin.nextLong();
		for (int i=0; i<n; i++)	cost[i] = stdin.nextLong();
		memo = new long[n][n];
		for (int i=0; i<n; i++) Arrays.fill(memo[i], -1);
		
		// Store cumulative frequency of people in range.
		cumfreq = new long[n+1];
		for (int i=1; i<=n; i++) cumfreq[i] = cumfreq[i-1] + nump[i-1];

		// Ta da!		
		System.out.println(go(0, n-1));
	}
	
	// Solve the problem for the states [i..j]
	public static long go(int i, int j) {
		
		// Base cases.
		if (i == j) return 0;
		if (memo[i][j] != -1) return memo[i][j];
		
		long res = 1000000000000000000L;
		
		// Try each split.
		for (int split=i; split<j; split++) {

			// We only want to go to the cheaper of the two possible convention spots.
			long taco = Math.min(cost[split], cost[split+1]);

			// Add cost of getting left and right plus tacos for this convention.
			// Use the cumulative frequency array to get the range sum quickly.
			long tmp = go(i,split) + go(split+1,j) + taco*(cumfreq[j+1]-cumfreq[i]);

			// Take the better answer.	
			res = Math.min(res, tmp);
		}
		
		// Store and return.
		return memo[i][j] = res;
	}
}